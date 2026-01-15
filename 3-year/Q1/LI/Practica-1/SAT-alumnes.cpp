#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

#define UNDEF -1
#define TRUE 1
#define FALSE 0
//variable es valor absolut
//literal no

uint var_max_confl; //Heuristic 2
uint max_confl = 0;

uint numVars;
uint numClauses;
vector<vector<int> > clauses;
vector<int> model; //guarda llista amb literals i el seu valor
vector<int> modelStack; //gurada la llista amb decide i propagate
uint indexOfNextLitToPropagate;
uint decisionLevel; //augmenta per cada decisio feta, 0 decisions val 0, 1 decisio val 1

vector<vector<uint>> occurList; //per cada literal l tindra una llista dels indexos de les clausules on apareix
vector<pair<uint,uint>> comptadorClausulesIniANDConfl; //per cada literal tindre un comptador per quantes vegades apareix a les clausules
vector<pair<uint,uint>> aux;

bool comp (pair<uint,uint> a, pair<uint,uint> b) {
  return a.second > b.second; //en v[0] esta el comptador més alt
}

void readClauses( ){
  // Skip comments
  char c = cin.get();
  while (c == 'c') {
    while (c != '\n') c = cin.get();
    c = cin.get();
  }  
  // Read "cnf numVars numClauses"
  string aux;
  cin >> aux >> numVars >> numClauses;

  clauses.resize(numClauses);
  occurList.resize((numVars + 1)*2+1); //vector de mida n on n = nombre de literals
  comptadorClausulesIniANDConfl.resize(numVars);

  // Read clauses
  for (uint i = 0; i < numClauses; ++i) {
    int lit;
    while (cin >> lit and lit != 0) {
      int lit2 = lit;
      clauses[i].push_back(lit); //va fent push_back de cada literal

      if (lit < 0) lit = -lit;
      else lit = (numVars + 1) + lit;
      occurList[lit].push_back(i); //guardem els indexos de les clausules on apareix lit

      lit = abs(lit2); // Heuristic 1
      comptadorClausulesIniANDConfl[lit].first = abs(lit2);
      ++comptadorClausulesIniANDConfl[lit].second;
    }
  }
}



int currentValueInModel(int lit){ //retorna UNDEF o valor logic
  if (lit >= 0) return model[lit];
  else {
    if (model[-lit] == UNDEF) return UNDEF;
    else return 1 - model[-lit];
  }
}


void setLiteralToTrue(int lit){
  modelStack.push_back(lit);
  if (lit > 0) model[lit] = TRUE;
  else model[-lit] = FALSE;		
}


//Primera part que s'ha de canviar, usar el occurList
bool propagateGivesConflict ( ) {
  while ( indexOfNextLitToPropagate < modelStack.size() ) {
    int lit = -modelStack[indexOfNextLitToPropagate]; //negat del següent literal a propagar :D
    int lit2 = lit;
    ++indexOfNextLitToPropagate;
    if (lit < 0) lit = -lit;
    else lit = (numVars + 1) + lit;
    uint numClauses_lit = occurList[lit].size(); //mirarem n clausules on surt el literal lit
    for (uint i = 0; i < numClauses_lit; ++i) {
        bool someLitTrue = false;
        int numUndefs = 0;
        int lastLitUndef = 0;
        uint clausula_x = occurList[lit][i]; //agafem index de clausula
        for (uint k = 0; not someLitTrue and k < clauses[clausula_x].size(); ++k){
            int val = currentValueInModel(clauses[clausula_x][k]);
            if (val == TRUE) someLitTrue = true;
            else if (val == UNDEF){ ++numUndefs; lastLitUndef = clauses[clausula_x][k]; }
        }
        if (not someLitTrue and numUndefs == 0) {
          ++comptadorClausulesIniANDConfl[abs(lit2)].second;
          if (comptadorClausulesIniANDConfl[abs(lit2)].second > max_confl) max_confl = comptadorClausulesIniANDConfl[abs(lit2)].second;
          var_max_confl = abs(lit2);
          if (max_confl == 50000) {
            for (uint i = 0; i < numVars+1; ++i) comptadorClausulesIniANDConfl[i].second /= 2;
            max_confl = 25000;
          }
          return true; // conflict! all lits false
        }
        else if (not someLitTrue and numUndefs == 1) setLiteralToTrue(lastLitUndef);
      }
  }
  return false;
}


void backtrack(){ //va retrocedint i posant undef on havia canviat algo amb propagate
  uint i = modelStack.size() -1;
  int lit = 0;
  while (modelStack[i] != 0){ // 0 is the DL mark
    lit = modelStack[i];
    model[abs(lit)] = UNDEF;
    modelStack.pop_back();
    --i;
  }
  // at this point, lit is the last decision
  modelStack.pop_back(); // remove the DL mark
  --decisionLevel;
  indexOfNextLitToPropagate = modelStack.size();
  setLiteralToTrue(-lit);  // reverse last decision
}


// Heuristic for finding the next decision literal:
// 1- Comptador de quantes vegades apareix una variable en totes les clausules, +alt millor
// 2- Comptador de conflictes recents, cada vegada que apareix un conflicte incrementa comptador d'aquelles variables
int getNextDecisionLiteral(){ //millorar!! buscar el que provoca mes conflictes
  aux = comptadorClausulesIniANDConfl;
  sort(aux.begin(), aux.end(), comp);
  for (uint i = 0; i < numVars+1; ++i) {//buscar variable amb mes clausules ini, comencem amb comptador mes alt, ordenat abans
    int var = aux[i].first;
    if (model[var] == UNDEF) return var;
  }
  return 0; // reurns 0 when all literals are defined
}




void checkmodel(){ //comprova que el model estigui be
  for (uint i = 0; i < numClauses; ++i){
    bool someTrue = false;
    for (uint j = 0; not someTrue and j < clauses[i].size(); ++j)
      someTrue = (currentValueInModel(clauses[i][j]) == TRUE);
    if (not someTrue) {
      cout << "Error in model, clause is not satisfied:";
      for (uint j = 0; j < clauses[i].size(); ++j) cout << clauses[i][j] << " ";
      cout << endl;
      exit(1);
    }
  }  
}

int main(){ 
  readClauses(); // reads numVars, numClauses and clauses
  model.resize(numVars+1,UNDEF);
  indexOfNextLitToPropagate = 0;  
  decisionLevel = 0;
  
  // Take care of initial unit clauses, if any
  for (uint i = 0; i < numClauses; ++i)
    if (clauses[i].size() == 1) {
      int lit = clauses[i][0];
      int val = currentValueInModel(lit);
      if (val == FALSE) {cout << "UNSATISFIABLE" << endl; return 10;}
      else if (val == UNDEF) setLiteralToTrue(lit);
    }
  
  // DPLL algorithm
  while (true) {
    while ( propagateGivesConflict() ) { //millorar!
      if ( decisionLevel == 0) { cout << "UNSATISFIABLE" << endl; return 10; }
      backtrack();
    }
    int decisionLit = getNextDecisionLiteral(); //millorar!
    if (decisionLit == 0) { checkmodel(); cout << "SATISFIABLE" << endl; return 20; }
    // start new decision level:
    modelStack.push_back(0);  // push mark indicating new DL, indiquem que ho hem escollit nosaltres
    ++indexOfNextLitToPropagate;
    ++decisionLevel;
    setLiteralToTrue(decisionLit);    // now push decisionLit on top of the mark
  }
}  
