#include "Player.hh"

/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Astornauta4
typedef vector<vector<int>> MatrixI;

struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }

  /**
   * Types and attributes for your player can be defined here.
   *///                          0    1      2    3     4   5   6   7
  const vector<Dir> dirs_gho = {Up, Down, Left, Right, DR, RU, LD, UL};
  const vector<Dir> dirs_mag = {Up, Down, Left, Right};
  map<Pos,bool> pos2bool;

  //altres variables:
  const int INF = numeric_limits<int>::max();
  int mags_ini = -1;
  int id_ghost = -1;
  int fase = 0; //0 llavors anar, 1 matar, 2 defendre

  //funcions:
  void mirar_on_llibres() {
    int n = board_rows();
    int m = board_cols();
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        pos2bool[Pos(i,j)] = false;
      }
    }
  }

  Dir cami_invers_m(Pos p, Pos u, const vector<vector<Dir>>& previ) {
    Dir resultat = Up;
    Pos aux = u;
    while (aux != p) {
      if (previ[aux.i][aux.j] == Down) {
        aux += Up;
        if (aux == p) resultat = Down;
      }
      else if (previ[aux.i][aux.j] == Up) {
        aux += Down;
        if (aux == p) resultat = Up;
      }
      else if (previ[aux.i][aux.j] == Right) {
        aux += Left;
        if (aux == p) resultat = Right;
      }
      else {
        aux += Right;
        if (aux == p) resultat = Left;
      }
    }
    return resultat;
  }

  Dir cami_invers_g(Pos p, Pos u, const vector<vector<Dir>>& previ) {
    Dir resultat = Up;
    Pos aux = u;
    while (aux != p) {
      if (previ[aux.i][aux.j] == Down) {
        aux += Up;
        if (aux == p) resultat = Down;
      }
      else if (previ[aux.i][aux.j] == Up) {
        aux += Down;
        if (aux == p) resultat = Up;
      }
      else if (previ[aux.i][aux.j] == Right) {
        aux += Left;
        if (aux == p) resultat = Right;
      }
      else if (previ[aux.i][aux.j] == Left) {
        aux += Right;
        if (aux == p) resultat = Left;
      }
      else if (previ[aux.i][aux.j] == DR) {
        aux += UL;
        if (aux == p) resultat = DR;
      }
      else if (previ[aux.i][aux.j] == RU) {
        aux += LD;
        if (aux == p) resultat = RU;
      }
      else if (previ[aux.i][aux.j] == LD) {
        aux += RU;
        if (aux == p) resultat = LD;
      }
      else {
        aux += DR;
        if (aux == p) resultat = UL;
      }
    }
    return resultat;
  }

  //Aquesta funció retorna la distància mínima a un enemic
  //i l'ultima direcció feta per arribar-hi
  pair<int,Dir> buscar_rival(Pos p) {
    bool found = false;
    pair<int,Dir> resultat;
    resultat.first = INF;
    resultat.second = Up;

    int n = board_rows();
    int m = board_cols();
    MatrixI distances (n, vector<int>(m, INF));
    vector<vector<Dir>> previ (n, vector<Dir>(m));

    distances[p.i][p.j] = 0;
    queue<Pos> Q;
    Q.push(p);

    int w;
    if (cell(p).id == id_ghost) w = 8;
    else w = 4;

    while (not Q.empty() and not found) {
      Pos v = Q.front();
      Q.pop();
      Pos u;
      for (int i = 0; not found and i < w; ++i) {
        if (cell(p).id == id_ghost) u = v + dirs_gho[i];
        else u = v + dirs_mag[i];

        if (pos_ok(u) and cell(u).type != Wall and distances[u.i][u.j] == INF) {
          Q.push(u);
          distances[u.i][u.j] = distances[v.i][v.j] + 1;
          if (cell(p).id == id_ghost) previ[u.i][u.j] = dirs_gho[i];
          else previ[u.i][u.j] = dirs_mag[i];
          if (cell(u).owner != -1 and cell(u).id != -1 and u != pos_voldemort()) {
            found = true;
            resultat.first = distances[u.i][u.j];
            if (cell(p).id == id_ghost) resultat.second = cami_invers_g(p, u, previ);
            else resultat.second = cami_invers_m(p, u, previ);
          }
        }
      }
    }
    return resultat;
  }



  //Aquesta funció retorna la distància mínima a un amic sense ser transformat
  //i l'ultima direcció feta per arribar-hi
  pair<int,Dir> seek_help(Pos p) {
    bool found = false;
    pair<int,Dir> resultat;
    resultat.first = INF;
    resultat.second = Up;

    int n = board_rows();
    int m = board_cols();
    MatrixI distances (n, vector<int>(m, INF));
    vector<vector<Dir>> previ (n, vector<Dir>(m));

    distances[p.i][p.j] = 0;
    queue<Pos> Q;
    Q.push(p);

    while (not Q.empty() and not found) {
      Pos v = Q.front();
      Q.pop();

      for (int i = 0; not found and i < 4; ++i) {
        Pos u = v + dirs_mag[i];
        if (pos_ok(u) and cell(u).type != Wall and distances[u.i][u.j] == INF) {
          Q.push(u);
          distances[u.i][u.j] = distances[v.i][v.j] + 1;
          previ[u.i][u.j] = dirs_mag[i];
          if (cell(u).owner == me() and cell(u).id != -1 and cell(u).id != id_ghost and not unit(cell(u).id).is_in_conversion_process()) {
            found = true;
            resultat.first = distances[u.i][u.j];
            resultat.second = cami_invers_m(p, u, previ);
          }
        }
      }
    }
    return resultat;
  }

  //Aquesta funció retorna la distància mínima a un amic transformant-se
  //i l'ultima direcció feta per arribar-hi
  pair<int,Dir> give_help(Pos p) {
    bool found = false;
    pair<int,Dir> resultat;
    resultat.first = INF;
    resultat.second = Up;

    int n = board_rows();
    int m = board_cols();
    MatrixI distances (n, vector<int>(m, INF));
    vector<vector<Dir>> previ (n, vector<Dir>(m));

    distances[p.i][p.j] = 0;
    queue<Pos> Q;
    Q.push(p);

    while (not Q.empty() and not found) {
      Pos v = Q.front();
      Q.pop();

      for (int i = 0; not found and i < 4; ++i) {
        Pos u = v + dirs_mag[i];
        if (pos_ok(u) and cell(u).type != Wall and distances[u.i][u.j] == INF) {
          Q.push(u);
          distances[u.i][u.j] = distances[v.i][v.j] + 1;
          previ[u.i][u.j] = dirs_mag[i];
          if (cell(u).owner == me() and cell(u).id != -1 and cell(u).id != id_ghost and unit(cell(u).id).is_in_conversion_process()) {
            found = true;
            resultat.first = distances[u.i][u.j];
            resultat.second = cami_invers_m(p, u, previ);
          }
        }
      }
    }
    return resultat;
  }

  //Aquesta funció retorna la distància mínima a un llibre
  //i l'ultima direcció feta per arribar-hi
  pair<int,Dir> found_book(Pos p) {
    bool found = false;
    pair<int,Dir> resultat;
    resultat.first = INF;
    resultat.second = Up;

    int n = board_rows();
    int m = board_cols();
    MatrixI distances (n, vector<int>(m, INF));
    vector<vector<Dir>> previ (n, vector<Dir>(m));

    distances[p.i][p.j] = 0;
    queue<Pos> Q;
    Q.push(p);

    while (not Q.empty() and not found) {
      Pos v = Q.front();
      Q.pop();

      for (int i = 0; not found and i < 4; ++i) {
        Pos u = v + dirs_mag[i];
        if (pos_ok(u) and cell(u).id == -1 and cell(u).type != Wall and distances[u.i][u.j] == INF) {
          Q.push(u);
          distances[u.i][u.j] = distances[v.i][v.j] + 1;
          previ[u.i][u.j] = dirs_mag[i];
          if (cell(u).book) {
            found = true;
            pos2bool[u] = true;
            resultat.first = distances[u.i][u.j];
            resultat.second = cami_invers_m(p, u, previ);
          }
        }
      }
    }
    return resultat;
  }

  //Aquesta funció retorna la distància mínima a un enemic
  //i l'ultima direcció feta per arribar-hi
  pair<int,Dir> found_enemy(Pos p) {
    bool found = false;
    pair<int,Dir> resultat;
    resultat.first = INF;
    resultat.second = Right;

    int n = board_rows();
    int m = board_cols();
    MatrixI distances (n, vector<int>(m, INF));
    vector<vector<Dir>> previ (n, vector<Dir>(m));

    distances[p.i][p.j] = 0;
    queue<Pos> Q;
    Q.push(p);

    while (not Q.empty() and not found) {
      Pos v = Q.front();
      Q.pop();

      for (int i = 0; not found and i < 4; ++i) {
        Pos u = v + dirs_mag[i];
        if (pos_ok(u) and (cell(u).id == -1 or (cell(u).id != -1 and unit(cell(u).id).player != me())) and cell(u).type != Wall and distances[u.i][u.j] == INF) {
          Q.push(u);
          distances[u.i][u.j] = distances[v.i][v.j] + 1;
          previ[u.i][u.j] = dirs_mag[i];
          if (cell(u).owner != me() and cell(u).owner != -1 and cell(u).id != -1 and u != pos_voldemort() and unit(cell(u).id).type != Ghost and not unit(cell(u).id).is_in_conversion_process()) {
            found = true;
            resultat.first = distances[u.i][u.j];
            resultat.second = cami_invers_m(p, u, previ);
          }
        }
      }
    }
    return resultat;
  }

  //Aquesta funció retorna la distància mínima a un enemic
  //i l'ultima direcció feta per arribar-hi
  pair<int,Dir> fugir(Pos p) {
    bool found = false;
    pair<int,Dir> resultat;
    resultat.first = INF;
    resultat.second = Up;

    int n = board_rows();
    int m = board_cols();
    MatrixI distances (n, vector<int>(m, INF));
    vector<vector<Dir>> previ (n, vector<Dir>(m));

    distances[p.i][p.j] = 0;
    queue<Pos> Q;
    Q.push(p);

    while (not Q.empty() and not found) {
      Pos v = Q.front();
      Q.pop();

      for (int i = 0; not found and i < 8; ++i) {
        Pos u = v + dirs_gho[i];
        if (pos_ok(u) and cell(u).id == -1 and cell(u).type != Wall and  distances[v.i][v.j] + 1 < distances[u.i][u.j]) {
          Q.push(u);
          distances[u.i][u.j] = distances[v.i][v.j] + 1;
          previ[u.i][u.j] = dirs_gho[i];
          if (cell(u).book or cell(u).owner == -1) {
            found = true;
            resultat.first = distances[u.i][u.j];
            resultat.second = cami_invers_g(p, u, previ);
          }
        }
      }
    }
    return resultat;
  }

  //Aquesta funció retorna la distància mínima de voldemort a un aliat
  //i l'ultima direcció feta per arribar-hi
  pair<int,Dir> voldemort_presence(Pos p) {
    bool found = false;
    pair<int,Dir> resultat;
    resultat.first = INF;
    resultat.second = Up;

    int n = board_rows();
    int m = board_cols();
    MatrixI distances (n, vector<int>(m, INF));
    vector<vector<Dir>> previ (n, vector<Dir>(m));

    distances[p.i][p.j] = 0;
    queue<Pos> Q;
    Q.push(p);

    while (not Q.empty() and not found) {
      Pos v = Q.front();
      Q.pop();

      for (int i = 0; not found and i < 8; ++i) {
        Pos u = v + dirs_gho[i];
        if (pos_ok(u) and cell(u).type != Wall and distances[u.i][u.j] == INF) {
          Q.push(u);
          distances[u.i][u.j] = distances[v.i][v.j] + 1;
          previ[u.i][u.j] = dirs_gho[i];
          if (cell(u).owner == me() and cell(u).id != -1) {
            found = true;
            resultat.first = cell(u).id;
            resultat.second = dirs_gho[i];
          }

          else if (cell(u).owner != me() and cell(u).owner != -1 and cell(u).id != -1) {
            found = true;
            resultat.first = -1;
          }
        }
      }
    }
    return resultat;
  }

  int sum_vector(const vector<int>& spell) {
    int resultat = 0;
    int n = spell.size();
    for (int i = 0; i < n; ++i) {
      resultat += spell[i];
    }
    return resultat;
  }

  vector<int> solve_spell(const vector<int>& spell) {
    int n = spell.size();

    int valor = sum_vector(spell) / 5;
    vector<int> copia(n);
    vector<bool> used(n, false);
    int grup = 0;

    for (int i = 0; i < n; ++i) {
      bool found = false;
      if (not used[i]) {
        for (int j = n-1; j >= 0; --j) {
          if (not used[j] and spell[i] + spell[j] < valor) {
            for (int k = i+1; not found and k <= j-1; ++k) {
              if (not used[k] and spell[i]+spell[j]+spell[k] == valor and k != i and k != j) {
                used[i] = true;
                used[j] = true;
                used[k] = true;
                copia[i] = grup;
                copia[j] = grup;
                copia[k] = grup;
                ++grup;
                found = true;
              }
            }
          }
        }
      }
    }
    return copia;
  }

  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
    //inicialització de variables
    if (round() == 0) {
      mags_ini = num_ini_wizards_per_clan();
      id_ghost = ghost(me());
    }

    mirar_on_llibres();


    //fugir de voldemort si cal
    pair<int,Dir> voldemort = voldemort_presence(pos_voldemort());
    if (voldemort.first == -1) {} //no cal fer res
    else { //cal fugir
      pair<int,Dir> mes_proxim = buscar_rival(unit(voldemort.first).pos);
      Pos new_pos = unit(voldemort.first).pos + mes_proxim.second;
      if (pos_ok(new_pos) and cell(new_pos).type != Wall) move(voldemort.first, mes_proxim.second);
    }


    //encantiri
    if (unit(id_ghost).resting_rounds() == 0 and round() <= num_rounds() * 3/4) {
      vector<int> spell_ing = spell_ingredients();
      vector<int> solution = solve_spell(spell_ing);
      spell(id_ghost, solution);
    }


    //moure el fantasme
    pair<int,Dir> fugida = fugir(unit(id_ghost).pos); //no vol movida, només vol caselles blanques i llibres
    Pos new_pos = unit(id_ghost).pos + fugida.second;
    if (pos_ok(new_pos) and cell(new_pos).type != Wall) move(id_ghost, fugida.second);


    //moure els mags
    vector<int> ids_mags = wizards(me());
    for (int id_wiz : ids_mags) {

      if (unit(id_wiz).is_in_conversion_process()) { //que vagi a per ajuda
        pair<int,Dir> cami0 = seek_help(unit(id_wiz).pos);
        if (cami0.first < rounds_for_converting_wizard()) {
          Pos new_pos = unit(id_wiz).pos + cami0.second;
          if (pos_ok(new_pos) and cell(new_pos).type != Wall) move(id_wiz, cami0.second);
        }
      }
      else {
        if (round() < num_rounds() -60) { //mode recolecta
          pair<int,Dir> cami0 = give_help(unit(id_wiz).pos);
          pair<int,Dir> cami1 = found_book(unit(id_wiz).pos);
          pair<int,Dir> cami2 = found_enemy(unit(id_wiz).pos);

          if (cami0.first < rounds_for_converting_wizard()) {
            Pos new_pos = unit(id_wiz).pos + cami0.second;
            if (pos_ok(new_pos) and cell(new_pos).type != Wall) move(id_wiz, cami0.second);
          }

          else if (cami2.first <= 1) {
            Pos new_pos = unit(id_wiz).pos + cami2.second;
            if (pos_ok(new_pos) and cell(new_pos).type != Wall) move(id_wiz, cami2.second);
          }
          else {
            Pos new_pos = unit(id_wiz).pos + cami1.second;
            if (pos_ok(new_pos) and cell(new_pos).type != Wall) move(id_wiz, cami1.second);
          }
        }

        else { //mode atac
          pair<int,Dir> cami0 = give_help(unit(id_wiz).pos);
          pair<int,Dir> cami1 = found_enemy(unit(id_wiz).pos);
          pair<int,Dir> cami2 = found_book(unit(id_wiz).pos);
          if (cami0.first < rounds_for_converting_wizard()) {
            Pos new_pos = unit(id_wiz).pos + cami0.second;
            if (pos_ok(new_pos) and cell(new_pos).type != Wall) move(id_wiz, cami0.second);
          }

          else if (cami1.first != INF) {
            Pos new_pos = unit(id_wiz).pos + cami1.second;
            if (pos_ok(new_pos) and cell(new_pos).type != Wall) move(id_wiz, cami1.second);
          }
          else {
            Pos new_pos = unit(id_wiz).pos + cami2.second;
            if (pos_ok(new_pos) and cell(new_pos).type != Wall) move(id_wiz, cami2.second);
          }
        }
      }
    }
  }
};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
