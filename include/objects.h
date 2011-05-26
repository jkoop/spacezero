 /*****************************************************************************
 **  This is part of the SpaceZero program
 **  Copyleft (C) 2006-2011  M.Revenga
 **
 **  This program is free software; you can redistribute it and/or modify
 **  it under the terms of the GNU General Public License (version 3), or
 **  (at your option) any later version, as published by the Free Software 
 **  Foundation.
 **
 **  This program is distributed in the hope that it will be useful,
 **  but WITHOUT ANY WARRANTY; without even the implied warranty of
 **  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 **  GNU General Public License for more details.
 **
 **  You should have received a copy of the GNU General Public License
 **  along with this program; if not, write to the Free Software
 **  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 ******************************************************************************/

/*************  SpaceZero  M.R.H. 2006-2011 ******************
		Author: M.Revenga
		E-mail: mrevenga at users.sourceforge.net
		version 0.80 May 2011
****/

#ifndef _OBJECTS_
#define _OBJECTS_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gtk/gtk.h>
#include "general.h"
#include "data.h"


#define VELMAX 60
#define VELMAX2 VELMAX*VELMAX
#define ACELMAX 600
#define VELANG .5
#define GASMAX 1000
#define STATEMAX 100


/* habitat modes */
#define H_SPACE 1
#define H_PLANET 2
#define H_SHIP 3

/* Obj modes */
#define NAV 1
#define LANDED 2


/* object types */
#define SHIP 1
#define PROJECTILE 2
#define PLANET 3
#define ASTEROID 4
#define ARTEFACT 5
#define TRACKPOINT 13
#define TRACE 14
#define ALLOBJS 31

/* objects subtypes */
/* ship subtypes (SHIP)*/
#define SHIP0 0
#define SHIP1 1
#define SHIP2 2
#define SHIP3 3
#define SHIP4 4
#define SHIP5 5
#define SHIP6 6
#define SHIPMAX SHIP6

#define PRICESHIP0 100
#define PRICESHIP1 100
#define PRICESHIP2 200
#define PRICESHIP3 300
#define PRICESHIP4 400
#define PRICESHIP5 200
#define PRICESHIP6 200

/* projectile subtypes (PROJECTILE)*/
#define SHOT0 20
#define SHOT1 21
#define SHOT2 22
#define SHOT3 23  // missile
#define SHOT4 24  /* laser */
#define EXPLOSION 25
#define MISSILE SHOT3
#define LASER SHOT4



/* predefined ships */ 
#define EXPLORER SHIP1
#define FIGHTER SHIP3
#define QUEEN SHIP4
#define SATELLITE SHIP5
#define TOWER SHIP6


/* weapons types */
#define CANNON0 0   /* no weapon */
#define CANNON1 1
#define CANNON2 2
#define CANNON3 3
#define CANNON4 4
#define CANNON5 5
#define CANNON6 6
#define CANNON7 7   /* velocity  */
#define CANNON8 8   /* missile */
#define CANNON9 9   /* laser */
#define NUMWEAPONS 10
#define CANNONMAX CANNON9

#define PRICECANNON0 0
#define PRICECANNON1 100
#define PRICECANNON2 150
#define PRICECANNON3 200
#define PRICECANNON4 400
#define PRICECANNON5 800
#define PRICECANNON6 1400
#define PRICECANNON7 1800   /* velocity  */
#define PRICECANNON8 2000   /* missile */
#define PRICECANNON9 2200   /* laser */

/* engine types */
#define ENGINE0 0 /* no engine */
#define ENGINE1 1 /* only turn */
#define ENGINE2 2
#define ENGINE3 3
#define ENGINE4 4
#define ENGINE5 5
#define ENGINEMAX ENGINE5

#define PRICEENGINE0 0
#define PRICEENGINE1 100
#define PRICEENGINE2 200
#define PRICEENGINE3 300
#define PRICEENGINE4 400
#define PRICEENGINE5 500

/* Planet states */
#define POWN 1
#define PALLY 2
#define PINEXPLORE 3
#define PENEMY 4
#define PUNKNOWN 5

/* Terrain types */
#define TERRAIN 0
#define LANDZONE 1


#define ASTEROID1 1
#define ASTEROID2 2
#define ASTEROID3 3

/* TODO ai players profiles */
#define PLAYERPROFDEFAULT 0   /* attack planets default profile*/
#define PLAYERPROFPACIFIST 1  /* never attack planets */
#define PLAYERPROFAGRESSIVE 2 /* */

/* ai players strategies */
#define NUMPLAYERSTRAT 3
#define PLAYERSTRATDEFAULT 0 /* attack near from near planet*/
#define PLAYERSTRATRANDOM 1  /* choose a random planet to attack */
#define PLAYERSTRATSTRONG 2  /* from strongest to nearest */

#define OBJNAMESMAXLEN 16  /*max size of objs names. */

struct _Segment{
  int x0,y0,x1,y1;
  int type;
  struct _Segment *next;
};

typedef struct _Segment Segment;

struct Tabla{
  int id,parent,dest,in,planet;
};

struct Planet{
  Segment *segment;  /* Planet terrain */
  int x,y;           /* coordinates of the planet */
  float r;           /* radio */
  float gold;        /* (0,...] */
  float reggold;     /* index of gold regeneration */
  //  int nships;        /* number of ships in planet */
  float A,B;         /* local, tmp variables */

};

struct Order{
  int priority;
  int id;
  int time;       /* duration of the order */
  int g_time;     /* order time */
  float a,b,c,d;  /* internal variables */
  float e,f,g,h;
  /*  struct Order *next; */
};


struct ListOrder{
  struct Order order;
  struct ListOrder *next;
};

typedef struct{
  int type;
  int durable;
  int life;
  int damage;
  int max_vel;
  int mass;
  int gascost;
  float unitcost;
}Projectile;

typedef struct{
  int type;
  int rate;       /* time the weapon is ready again */
  int nshots;     /* number of shots */
  int cont1;      /* if !=0 cant shot again */ 
  int mass;       /* mass of the projectile */
  int n;          /* number of ammunition */
  int max_n;      /* capacity */
  Projectile projectile;
}Weapon;

typedef struct{
  int type;
  int a_max;        /* max accel */
  int a;            /* increment of acceleration */
  int v_max;        /* max speed */
  int v2_max;       /* max speed 2 */
  float ang_a;      /* increment angular acceleration */
  float ang_a_max;  /* max angular acceleration */
  float ang_v_max;  /* max angular velocity */
  float gascost;    /* cost of gas */
  int mass;         /* mass of the engine */
}Engine;

typedef struct{
  struct _Object *obj[4]; /* use to point to 4 objects 
			     enemy ship, 
			     planets: enemy, inexplore and ally  */
  float d2[4];   /* distance2 to these objects */
  int td2[4];    /* time when such info is updated */
  int mlevel;    /* if there is a near high level SHIP */
  int tmlevel;
  int a,b;         /* low fuel stop switch */
}Data;


struct _Object{
  int id;           /* global identifier */
  int pid;          /* player identifier */
  char name[OBJNAMESMAXLEN];   /* object name */
  short player;
  short type;       /* type: SHIP,PLANET,PROJECTILE,... */

  short subtype;    /* object subtype */
  short level;
  float experience;
  int kills;        /*number of enemies killed */

  int durable;
  int visible;      /* not used */
  int selected;     /* if ship is selected for an order */
  int radar;        /* radar range */
  int mass;         /* mass */

  int cargo;        /* capacity of the bodega TODO*/
  int radio;        /* ship radio */
  float cost;       /* cost of the object per unit time*/
  int damage;       /* damage of the ship in collision*/

  short ai;         /* -1: by keyboard. [0,10] */
  short modified;   /* SENDOBJMOD, SENDOBJMOD0, etc, must be updated by net */
  short ttl;        /* if !=0 dont send  */
  short habitat;    /* free space or planet (H_SPACE H_PLANET)*/
  short mode;       /* LANDED, NAV(EGATING)  */

  float x,y;        /* position */
  float x0,y0;      /* old position */  
  float vx,vy;      /* velocity */
  float fx,fy;      /* new force */
  float fx0,fy0;    /* old force */

  float a;          /* ship angle */
  float ang_v;      /* angular velocity */
  float ang_a;      /* angular acceleration */
  float accel;      /* linear acceleration */
  float gas;        /* gas */
  float gas_max;    /* gas capacity */
  float life;       /* time life */
  float shield;     /* shield [0,1]*/
  float state;      /* estate of the ship %[0,100]*/

  float dest_r2;    /* distance**2 to the nearest object */
  int sw;
  short trace;
  int norder;       /* number of pending orders */
  struct Order actorder;
  struct _Object *parent;     /* pointer to parent obj */
  struct _Object *dest;       /* pointer to nearest enemy object */
  struct _Object *in;         /* Object in which is contained */ 
  struct Planet *planet;
  struct ListOrder *lorder;

  Weapon *weapon;     /*weapon selected 0 1 2*/
  Weapon weapon0;     /* actual weapon */
  Weapon weapon1;     /* actual weapon */
  Weapon weapon2;     /* actual weapon */
  Engine engine;      /* motor */
  Data *cdata;         /* data base */
};
typedef struct _Object Object;


struct ObjectAll{ /* SENDOBJALL */
  int id;           /* global identifier */
  int pid;          /* player identifier */
  char name[OBJNAMESMAXLEN];   /* object name */
  short player;
  short type;       /* type: SHIP,PLANET,PROJECTILE,... */
  short subtype;    /* object subtype */

  short level;
  float experience;
  int kills;        /*number of enemies killed */

  int durable;
  int visible;      /* not used */
  int selected;     /* if ship is selected for an order */
  int radar;        /* radar range */
  int mass;         /* mass */

  int cargo;        /* capacity of the bodega TODO*/
  int radio;        /* ship radio */
  float cost;       /* cost of the object per unit time*/
  int damage;       /* damage of the ship in collision*/

  short ai;         /* -1: by keyboard. [0,10] */
  short modified;   /* SENDOBJMOD, SENDOBJMOD0, etc, must be updated by net */
  short ttl;        /* if !=0 dont send  */
  short habitat;    /* free space or planet (H_SPACE H_PLANET)*/
  short mode;       /* LANDED, NAV(EGATING)  */

  float x,y;        /* position */
  float x0,y0;      /* old position */  
  float vx,vy;      /* velocity */
  float fx,fy;      /* new force */
  float fx0,fy0;    /* old force */

  float a;          /* ship angle */
  float ang_v;      /* angular velocity */
  float ang_a;      /* angular acceleration */
  float accel;      /* linear acceleration */
  float gas;        /* gas */
  float gas_max;    /* gas capacity */
  float life;       /* time life */
  float shield;     /* shield [0,1]*/
  float state;      /* estate of the ship %[0,100]*/

  float dest_r2;    /* distance**2 to the nearest object */
  int sw;
  short trace;
 
  int norder;       /* number of pending orders */
  struct Order actorder;

  int parent;     /* pointer to parent obj */
  int dest;       /* pointer to nearest enemy object */
  int in;         /* Object in which is contained */ 
  //  struct ListOrder *lorder;

  int weapon;     /*weapon selected 0 1 2*/
  Weapon weapon0;     /* actual weapon */
  Weapon weapon1;     /* actual weapon */
  Weapon weapon2;     /* actual weapon */
  Engine engine;      /* motor */
  //  Data *cdata;         /* data base */
};




struct ObjectNew{ /* SENDOBJNEW */
  int id;         /* identificador */
  /*  char name[OBJNAMESMAXLEN];*/ /*    object name  */
  short player;
  short type;       /* type: SHIP,PLANET,PROJECTILE,... */

  short subtype;    /* subtipo de objeto */
  /*  int level; */
  /*  float experience; */
  /*  int points; */

  int durable;
  /*  int visible; */
  //  int radar;     /* radar range */
  //  int mass;      /* mass */

  //  int cargo;     /* capacity of the bodega TODO*/
  int radio;      /* ship radio */
  //  float cost;     /* cost of the object per unit time*/
  int damage;     /* damage of the ship */

  short ai;         /* -1: by keyboard. [0,10] */
  short modified;   /* SENDOBJMOD, SENDOBJMOD0, etc, must be updated by net */
  //  int ttl;        /* if !=0 dont send  */
  short habitat;    /* free space or planet (H_SPACE H_PLANET)*/
  short mode;       /* LANDED, NAV(EGATING)  */

  float x,y;      /* position */
  //  float x0,y0;    /* old position */
  float vx,vy;    /* velocity */
  //  float fx,fy;    /* new force */
  // float fx0,fy0;  /* old force */

  float a;        /* ship angle */
  //  float ang_v;    /* angular velocity */
  //  float ang_a;    /* angular acceleration */
  //  float accel;     /* linear acceleration */
  float gas;      /* gas */
  //  float gas_max;  /* gas capacity */
  float life;     /* time life */
  //  float shield;   /* shield [0,1]*/
  //  float state;    /* estate of the ship %[0,100]*/

  //  float dest_r2;  /* distance**2 to the nearest object */
  //  int sw;
  //  int trace;
  //  int norder;     /* numero  de ordenes pendientes */
  //  struct Order actorder;
  int parent;     /* pointer to parent obj */
  int in;         /* Object in which is contained */ 
  int planet;
  //struct ListOrder *lorder;


  //  Weapon *weapon;            /*weapon selected 0 1 2*/
  //  Weapon weapon0;              /* actual weapon */
  // Weapon weapon1;              /* actual weapon */
  //Weapon weapon2;              /* actual weapon */
  //Engine engine;              /* engine */
  int engtype;
};



struct ObjectAAll{  /* SENDOBJAALL */
  int id;         /* identificador */
  //  int visible;  // not used
  short level;
  //  int kills;
  short habitat;    /* free space or planet */
  short mode;       /* LANDED, NAVEGATING  */
  float x,y;      /* posicion actual */
  float x0,y0;    /* posicion anterior */  
  float vx,vy;    /* velocidad actual */  

  float a;        /* angulo nave */
  float ang_v;    /* velocidad angular */
  float ang_a;    /* angular acceleration */
  float accel;     /* aceleracion */

  float gas;      /* combustible */
  float life;     /* tiempo de vida */
  //  float shield;   /* escudo [0,1]*/
  float state;    /* estado de la nave %[0,100]*/

  int in;         /* Object in which is contained */ 
};


struct Objectdynamic{ /* SENDOBJMOD */
  int id;          /* identificador */
  short level;
  short habitat;   /* free space or planet */
  short mode;      /* LANDED, NAVEGATING  */
  float x,y;       /* posicion actual */
  float x0,y0;     /* posicion anterior */   
  float vx,vy;     /* velocidad actual */ 
  float a;         /* angulo nave */
  float ang_v;     /* velocidad angular */
  float ang_a;     /* angular acceleration */
  float accel;     /* aceleracion */

  float state;     /* estado de la nave %[0,100]*/
};

struct Objectpos{  /* SENDOBJMOD0 */
  int id;         /* identificador */
  float x,y;      /* posicion actual */
  //  float x0,y0;    /* posicion anterior */
  //  float a;        /* angulo nave */
};

struct NearObject{
  Object *obj;
  float d2;
};

struct ObjList{
  Object *obj;
  struct ObjList *next;
};

struct HeadObjList{
  int n;
  struct ObjList *next;
};

struct ObjTree{
  Object *obj;
  struct ObjTree *next;
  struct ObjTree *in;
};

struct VerletList{
  Object *obj;
  struct ObjList *nextobj;
  struct VerletList *next;
};


struct Habitat{
  int type;      /* H_SPACE, H_PLANET , H_SHIP */
  Object *obj;
};

struct Global{
  int actual_player;
  int g_objid,g_projid;
  int ship_c,cv;
  int habitat_type;
  int habitat_id;
  int fobj[4];
};

struct Player{
  char playername[PLAYERNAMEMAXLEN]; /* name of the player */
  short id;          /* player id */
  int pid;         /* last ship player id  */
  short proc;        /* machine that controls it */
  short control;     /* HUMAN or COMPUTER */
  short team;        /* each player belongs to a team */
  short profile;     /* */
  short strategy;    /* */
  short maxlevel;    /* max ship level reached */
  int color;       /*    */
  int cv;          /* id of the actual ship */
  int nplanets;    /* number of players planets */
  int nships;      /* number of players ships */
  int nbuildships; /* number of ships created */
  float gold;      /* actual gold of the player */ 
  float balance;
  int lastaction;  /* buy or upgrade */
  int ndeaths;     /* number of casualties */
  int nkills;      /* number of enemies killed  */
  int points;      /*  */
  short modified;    /* used in communication */
  short ttl;

  struct IntList *kplanets;
  struct HeadIntIList ksectors;
};

struct PlayerAll{
  char playername[PLAYERNAMEMAXLEN]; /* name of the player */
  short id;          /* player id */
  int pid;         /* last ship player id  */
  short proc;        /* machine that controls it */
  short control;     /* HUMAN or COMPUTER */
  short team;        /* each player belongs to a team */
  short profile;     /* */
  short strategy;    /* */
  short maxlevel;    /* max ship level reached */
  int color;       /*    */
  int cv;          /* id of the actual ship */
  int nplanets;    /* number of players planets */
  int nships;      /* number of players ships */
  int nbuildships; /* number of ships created */
  float gold;      /* actual gold of the player */ 
  float balance;
  int lastaction;  /* buy or upgrade */
  int ndeaths;     /* number of casualties */
  int nkills;      /* number of enemies killed  */
  int points;      /*  */
  short modified;    /* used in communication */
  short ttl;
};



struct PlayerMod{  /* Used in communication  */
  short id;
  short nplanets;    /* number of players planets */
  short nships;      /* number of players ships */
  short nbuildships; /* number of ships created */
  float gold;      /* actual gold of the player */ 
  short ndeaths;     /* number of casualties */
  short nkills;      /* number of enemies killed  */
  int points;      /*  */
};


/* function Declarations */

int CopyObject(Object *obj,Object *nobj);
void Experience(Object *obj,float points);
Object *NewObj(struct HeadObjList *lhobjs,int type,int stype,
	       int x,int y,float vx,float vy,
	       int weapontype,int engtype,int,Object *parent,Object *in);
void NewWeapon(Weapon *weapon,int type);
void NewEngine(Engine *eng,int type);
struct Planet *NewPlanet(void);
int GetSegment(Segment *segment,Object *obj);
int GetLandedZone(Segment *segment,struct Planet *planet);

Object *RemoveDeadObjs(struct HeadObjList *lhobjs,Object *);
void RemoveObj(struct HeadObjList *lhobjs,Object *obj2remove);

int CountObjs(struct HeadObjList *lh,int player,int type,int subtype);
int CountShipsInPlanet(struct HeadObjList *lh,int planetid,int type,int subtype,int max);
int CountPlayerShipObjs(struct HeadObjList *lh,int player,int *cont);
int CountPlayerPlanets(struct HeadObjList *lh,struct Player player,int *cont);
int CountPlanets(struct HeadObjList *lh,int type);
int CountModObjs(struct HeadObjList *lh,int type);


void PrintObj(Object *obj);

Object *SelectObj(struct HeadObjList *lh,int id);
Object *SelectpObj(struct HeadObjList *lh,int id,int player);
Object *SelectObjInObj(struct HeadObjList *lh,int id,int player);
Object *SelectpObjInObj(struct HeadObjList *lh,int pid,int player);
Object *PrevCv(struct HeadObjList *lh,Object *,int);
Object *NextCv(struct HeadObjList *lh,Object *,int);
Object *FirstShip(struct HeadObjList *lh,Object *cv0,int pid);

Object *NextPlanetCv(struct HeadObjList *lh,Object *cv0,int pid);
Object *PrevPlanetCv(struct HeadObjList *lh,Object *cv0,int pid);

void Explosion(struct HeadObjList *lh,Object *obj);

void NearestObjAll(struct HeadObjList *lhc,Object *obj,struct NearObject *objs);
Object *NearestObj(struct HeadObjList *lh,Object *obj,int type,int status,float *d2);
int NearestObjs(struct HeadObjList *lh,Object *obj,int type,int status,int n,struct NearObject *objs);

void DestroyAllObj(struct HeadObjList *lh);
void DestroyObj(Object *obj);
void DestroyPlanet(struct Planet *planet);


int Add2TextMessageList(struct TextMessageList *lh,char *cad,int source,int dest,int mid,int time,int value);

int Add2ObjList(struct HeadObjList *lhobjs,Object *obj);
int DestroyObjList(struct HeadObjList *lh);
int CountObjList(struct HeadObjList *hlist);
int PrintObjList(struct HeadObjList *hl);
int IsInObjList(struct HeadObjList *lhobjs,Object *obj);
void KillAllObjs(struct HeadObjList *);
void DestroyAllPlayerObjs(struct HeadObjList *lh,int player);

int CreatePlayerList(struct HeadObjList list1,struct HeadObjList *list2,int);
int CreateContainerLists(struct HeadObjList *lh,struct HeadObjList *hcontainer);
int CreatekplanetsLists(struct HeadObjList *lh,struct HeadObjList *hkplanets);
int CreatePlanetList(struct HeadObjList,struct HeadObjList *);
void CreateNearObjsList(struct HeadObjList *lh,struct HeadObjList *lhn,int player);


int Add2TextList(struct TextList *head,char *cad,int color);
int DestroyTextList(struct TextList *head);
int PrintTextList(struct TextList *head);
int PosTextList(struct TextList *head,int m);
int CountTextList(struct TextList *head);
char Type(Object *obj);


int Cuadrante(float x, float y);
void InvCuadrante(int n,int *x, int *y);
int NearestSector(struct HeadIntIList *head,float a,float b);
int NearRandomSector(struct HeadIntIList *head,float a,float b);

int UpdateSectors(struct HeadObjList lh);
int GetPrice(Object *obj,int sid,int eng,int weapon);
int BuyShip(struct Player player,Object *obj,int type);


Object *MarkObjs(struct HeadObjList *lh,Region reg);
int UnmarkObjs(struct HeadObjList *lh);
int PrintSelected(struct HeadObjList *lh);
int CountSelected(struct HeadObjList *lh);
int NearMaxLevelObj(Object *obj,struct HeadObjList *lh);
int PlanetEmpty(Object *planet,Object *obj);


int UpdateCell(struct HeadObjList *lh,int *cell);
int ValueCell(int *cell,Object *obj);



/*************************/

struct ObjTree *Add2ObjTree(struct ObjTree *,Object *);
struct ObjTree *DelObjTree(struct ObjTree *head,Object *obj);
void DestroyTree(struct ObjTree *head);
void PrintObjTree (struct ObjTree *);
int IsInObjTree(struct ObjTree *,int );
struct ObjTree *Look4ObjTree(struct ObjTree *,Object *);


struct VerletList *CreateVerletList(struct HeadObjList hol);
void PrintVerletList(struct VerletList *hvl);
void DestroyVerletList(struct VerletList *hvl);



#endif
