#include "Player.hh"

/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Harry
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

  //altres variables:
  const int INF = numeric_limits<int>::max();
  int mags_ini = -1;
  int id_ghost = -1;


  //funcions:
  //Aquesta funció retorna la distància mínima a un amic sense ser transformat
  //i l'ultima direcció feta per arribar-hi
  pair<int,Dir> seek_help(Pos p) {
    bool found = false;
    pair<int,Dir> resultat;
    resultat.first = INF;

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
            Pos aux = u;
            while (aux != p) {
              if (previ[aux.i][aux.j] == Down) {
                aux += Up;
                if (aux == p) resultat.second = Down;

              }

              else if (previ[aux.i][aux.j] == Up) {
                aux += Down;
                if (aux == p) resultat.second = Up;
              }

              else if (previ[aux.i][aux.j] == Right) {
                aux += Left;
                if (aux == p) resultat.second = Right;
              }

              else {
                aux += Right;
                if (aux == p) resultat.second = Left;
              }
            }
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
            Pos aux = u;
            while (aux != p) {
              if (previ[aux.i][aux.j] == Down) {
                aux += Up;
                if (aux == p) resultat.second = Down;

              }

              else if (previ[aux.i][aux.j] == Up) {
                aux += Down;
                if (aux == p) resultat.second = Up;
              }

              else if (previ[aux.i][aux.j] == Right) {
                aux += Left;
                if (aux == p) resultat.second = Right;
              }

              else {
                aux += Right;
                if (aux == p) resultat.second = Left;
              }
            }
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
          if (cell(u).book) {
            found = true;
            resultat.first = distances[u.i][u.j];
            Pos aux = u;
            while (aux != p) {
              if (previ[aux.i][aux.j] == Down) {
                aux += Up;
                if (aux == p) resultat.second = Down;

              }

              else if (previ[aux.i][aux.j] == Up) {
                aux += Down;
                if (aux == p) resultat.second = Up;
              }

              else if (previ[aux.i][aux.j] == Right) {
                aux += Left;
                if (aux == p) resultat.second = Right;
              }

              else {
                aux += Right;
                if (aux == p) resultat.second = Left;
              }
            }
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
          if (cell(u).owner != me() and cell(u).owner != -1 and u != pos_voldemort()) {
            found = true;
            resultat.first = distances[u.i][u.j];
            Pos aux = u;
            while (aux != p) {
              if (previ[aux.i][aux.j] == Down) {
                aux += Up;
                if (aux == p) resultat.second = Down;

              }

              else if (previ[aux.i][aux.j] == Up) {
                aux += Down;
                if (aux == p) resultat.second = Up;
              }

              else if (previ[aux.i][aux.j] == Right) {
                aux += Left;
                if (aux == p) resultat.second = Right;
              }

              else {
                aux += Right;
                if (aux == p) resultat.second = Left;
              }
            }
          }
        }
      }
    }
    return resultat;
  }


  //Aquesta funció retorna la distància mínima a un enemic
  //i l'ultima direcció feta per arribar-hi
  pair<int,Dir> found_enemy_g(Pos p) {
    bool found = false;
    pair<int,Dir> resultat;
    resultat.first = INF;

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
          if (cell(u).owner != me() and cell(u).owner != -1 and u != pos_voldemort()) {
            found = true;
            resultat.first = distances[u.i][u.j];
            if (i % 2 != 0) resultat.second = dirs_gho[i-1]; //fem la reversa, volem fugir
            else resultat.second = dirs_gho[i+1];
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
          previ[u.i][u.j] = dirs_mag[i];
          if (cell(u).owner != me() and cell(u).owner != -1 and u != pos_voldemort()) {
            found = true;
            resultat.first = distances[u.i][u.j];
            if (i % 2 != 0) resultat.second = dirs_gho[i-1]; //fem la reversa, volem fugir
            else resultat.second = dirs_gho[i+1];
          }
        }
      }
    }
    return resultat;
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

    //moure el fantasme
    if (unit(id_ghost).last_attack_received() == -1) {
      pair<int,Dir> fugir = found_enemy_g(unit(id_ghost).pos);
      if (fugir.first != INF) {
        Pos new_pos = unit(id_ghost).pos + fugir.second;
        if (pos_ok(new_pos) and cell(new_pos).type != Wall) move(id_ghost, fugir.second);
      }
    }



    //moure els mags
    vector<int> ids_mags = wizards(me());
    for (int id_wiz : ids_mags) {

      if (unit(id_wiz).is_in_conversion_process()) { //que vagi a per ajuda
        pair<int,Dir> cami0 = seek_help(unit(id_wiz).pos);
        if (cami0.first != INF and cami0.first < rounds_for_converting_wizard()) {
          Pos new_pos = unit(id_wiz).pos + cami0.second;
          if (pos_ok(new_pos) and cell(new_pos).type != Wall) move(id_wiz, cami0.second);
        }
      }
      else {
        pair<int,Dir> cami0 = give_help(unit(id_wiz).pos);
        pair<int,Dir> cami1 = found_book(unit(id_wiz).pos);
        pair<int,Dir> cami2 = found_enemy(unit(id_wiz).pos);

        if (cami0.first != INF and cami0.first < rounds_for_converting_wizard()) {
          Pos new_pos = unit(id_wiz).pos + cami0.second;
          if (pos_ok(new_pos) and cell(new_pos).type != Wall) move(id_wiz, cami0.second);
        }

        if (cami1.first > cami2.first) { //enemy mes aprop
          Pos new_pos = unit(id_wiz).pos + cami2.second;
          if (pos_ok(new_pos) and cell(new_pos).type != Wall) move(id_wiz, cami2.second);
        }

        else if (cami1.first < cami2.first) { //book mes aprop
          Pos new_pos = unit(id_wiz).pos + cami1.second;
          if (pos_ok(new_pos) and cell(new_pos).type != Wall) move(id_wiz, cami1.second);
        }

        else { //igual distancia, anirem al enemy
          Pos new_pos = unit(id_wiz).pos + cami2.second;
          if (pos_ok(new_pos) and cell(new_pos).type != Wall) move(id_wiz, cami2.second);
        }
      }
    }
  }
};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
