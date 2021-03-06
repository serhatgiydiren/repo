enum LEGS = {spin, leap, waltz, curtsey, prep, stand};
enum ARMS = {beckon, out, up, wrapped, neutral};
enum FACE = {smile, wink, batt, think, glow, blank};

int: maxlen;
set of int: STEP = 1..maxlen;
array[LEGS] of int: maxlegs;
array[ARMS] of int: maxarms;
array[FACE] of int: maxface;

constraint assert(maxlegs[stand] >= maxlen, "maxlegs[stand] smaller than maxlen");
constraint assert(maxarms[neutral] >= maxlen, "maxarms[neutral] smaller than maxlen");
constraint assert(maxface[blank] >= maxlen, "maxface[blank] smaller than maxlen");
array[LEGS,ARMS] of int: dance_value;
array[ARMS,FACE] of int: entice_value;
constraint assert(dance_value[stand,neutral] = 0, "incorrect dance_value array");
constraint assert(entice_value[neutral,blank] = 0, "incorrect entice_value array");
int: boredom; % how bored each step make the viewer

var STEP: len;
array[STEP] of var LEGS: legs;
array[STEP] of var ARMS: arms;
array[STEP] of var FACE: face;

constraint legs[1]!=leap;
constraint forall(i in 2..maxlen)(legs[i]=leap -> legs[i-1]=prep);
constraint forall(i in 1..maxlen-1)(legs[i]=spin -> legs[i+1] in {curtsey,prep,stand});
constraint forall(i in 1..maxlen-1)(legs[i]=leap -> legs[i+1] in {spin,waltz,stand});
constraint forall(i in 1..maxlen-2)(legs[i]=waltz /\ legs[i+1]=waltz -> legs[i+2]!=waltz);
constraint forall(i in 1..maxlen-1)(legs[i]=curtsey -> legs[i-1]!=prep);
constraint forall(i in 1..maxlen-1)(legs[i]=waltz -> forall(j in i+1..maxlen)(legs[j]=curtsey -> exists(k in i+1..j-1)(legs[k]=stand)));

constraint arms[1]!=up;
constraint arms[1]!=beckon;
constraint forall(i in 2..maxlen)(arms[i]=beckon -> arms[i-1] in {out,up});
constraint forall(i in 2..maxlen)(arms[i]=wrapped -> arms[i-1] in {beckon,neutral});
constraint forall(i in 1..maxlen-1)(arms[i]=arms[i+1] -> arms[i]=neutral);

constraint forall(i in 1..maxlen-2) (face[i]=face[i+1] /\ face[i+1]=face[i+2] -> face[i]=blank);
constraint forall(i in 2..maxlen)(face[i]=think -> face[i-1] in {wink,think,glow,blank});

constraint forall(i in STEP)(dance_value[legs[i],arms[i]]>=0);
constraint forall(i in STEP)(entice_value[arms[i],face[i]]>=0);

include "globals.mzn";
constraint global_cardinality_low_up(legs, LEGS, [0|t in legs], maxlegs);
constraint global_cardinality_low_up(arms, ARMS, [0|t in arms], maxarms);
constraint global_cardinality_low_up(face, FACE, [0|t in face], maxface);

constraint forall(i in STEP)(i>len -> legs[i]=stand /\ arms[i]=neutral /\ face[i]=blank);
                            
var int : obj;
constraint obj = sum(i in 1..len)(dance_value[legs[i],arms[i]]+entice_value[arms[i],face[i]])-boredom*len;
solve maximize obj;
