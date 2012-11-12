/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]            = "Droid Sans Mono:size=9:Bold:antialias=true";
#define NUMCOLORS 5
static const char colors[NUMCOLORS][ColLast][8] = {
  // border   foreground background
  { "#636363", "#848484", "#222222" },  // normal
  { "#ffffff", "#AD6500", "#222222" },  // selected
  { "#2E2E2E", "#FF8278", "#222222" },  // urgent/warning  (black on yellow)
  { "#2E2E2E", "#556B2F", "#222222" },  // occupied
  { "#2E2E2E", "#ffffff", "#222222" },  // error (white on red)
};
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */

// configure systray diff
static const unsigned int systrayspacing	= 2;		/* systray spacing */
static const Bool showsystray				= True;     /* False means no systray */

// class, instance and title can be found out by issuing xprop(1)
//  WM_CLASS(STRING) = instance, class, WM_NAME(STRING) = title
static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Firefox",	       NULL,       NULL,           2,            False,        -1 },
};

#include "c/gaplessgrid.c"

/* layout(s) */
static const float mfact      = 0.55; 	/* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    	/* number of clients in master area */
static const Bool resizehints = False; 	/* True means respect size hints in tiled resizals */
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    	/* first entry is default */
	{ "><>",      NULL },    	/* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "###",      gaplessgrid },
	{ "===",	  bstack },
};

/* tagging */
static const Tag tags[] = {
    /* name    layout       mfact  nmaster*/
    { "HOME",	&layouts[0], -1,    -1 },
    { "WWW",	&layouts[0], -1,	-1 },
    { "TERM",	&layouts[0], -1,    -1 },
    { "EMAIL",	&layouts[0], -1,    -1 },
    { "MEDIA",	&layouts[0], -1,    -1 },
};

// import nextprevtag
#include "c/nextprevtag.c"
#include "c/push.c"

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[]		= { "dmenu_run", "-fn", font, NULL };
static const char *termcmd[]  		= { "urxvt", NULL };
static const char *browsercmd[]  	= { "firefox",	NULL };
static const char *filemanagercmd[] = { "nautilus", "--no-desktop",	NULL };
static const char *mailcmd[]  		= { "urxvt", "-e", "mutt" ,NULL };
static const char *quitcmd[]  		= { "dmenu_shutdown" ,NULL };
static const char *helpcmd[]  		= { "dmenu_mon" ,NULL };
static const char *scriptscmd[] 	= { "dmenu_scripts" ,NULL };
static const char *pythoncmd[] 	    = { "dmenu_python" ,NULL };
static const char *ncmpcppcmd[]  	= { "urxvt", "-e",	"ncmpcpp", NULL };
static const char *alsamixercmd[]  	= { "urxvt", "-e",	"alsamixer", NULL };
static const char *wicdcmd[]		= { "urxvt", "-e",	"wicd-curses", NULL };
static const char *playpausecmd[]  	= { "mpc", "toggle", NULL };
static const char *prevcmd[]  		= { "mpc", "prev", NULL };
static const char *nextcmd[] 	 	= { "mpc", "next", NULL };
static const char *volupcmd[]		= { "amixer", "set", "Master", "5%+", NULL };
static const char *voldowncmd[]		= { "amixer", "set", "Master", "5%-", NULL };
//static const char *volupcmd[] 		= { "dvol", "-i", "5", NULL };
//static const char *voldowncmd[] 	= { "dvol", "-d", "5", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,						XK_Return, spawn,          {.v = termcmd } },
	//{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)

	{ MODKEY|ShiftMask,             XK_q, spawn,               {.v = quitcmd } },
	{ MODKEY,                       XK_g, setlayout,           {.v = &layouts[3] } },
	{ MODKEY,                       XK_b, setlayout,           {.v = &layouts[4] } },

	{ MODKEY|ShiftMask,             XK_b, spawn,               {.v = browsercmd } },
	{ MODKEY|ShiftMask,             XK_f, spawn,               {.v = filemanagercmd } },
	{ MODKEY|ShiftMask,             XK_m, spawn,               {.v = mailcmd } },
	{ MODKEY|ShiftMask,             XK_n, spawn,               {.v = ncmpcppcmd } },
	{ MODKEY|ShiftMask,				XK_w, spawn,               {.v = wicdcmd } },
	{ MODKEY|ShiftMask,				XK_h, spawn,               {.v = helpcmd } },
	{ MODKEY|ShiftMask,				XK_s, spawn,               {.v = scriptscmd } },
	{ MODKEY|ShiftMask,				XK_p, spawn,               {.v = pythoncmd } },

	{ MODKEY|ShiftMask,		XK_a, spawn,               {.v = alsamixercmd } },
	{ MODKEY,		        XK_backslash, spawn,       {.v = playpausecmd } },
	{ MODKEY,		        XK_bracketleft, spawn,     {.v = prevcmd } },
	{ MODKEY,		        XK_bracketright, spawn,    {.v = nextcmd } },
	{ MODKEY,		        XK_equal, spawn,           {.v = volupcmd } },
	{ MODKEY,		        XK_minus, spawn,           {.v = voldowncmd } },

	//{ MODKEY|ShiftMask,     XK_c, spawn,	           {.v = selectioncopy } },
	//{ MODKEY|ShiftMask,     XK_v, spawn,	           {.v = selectionpaste } },

	// nextprevtag.c config
    { MODKEY,		                XK_Right,    view_adjacent,  { .i = +1 } },
    { MODKEY,	                    XK_Left,     view_adjacent,  { .i = -1 } },

    { MODKEY|ControlMask,           XK_j,			pushdown,       {0} },
    { MODKEY|ControlMask,           XK_k,           pushup,         {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	//{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },

	// nextprevtag.c config
    { ClkTagBar,            0,              Button4,        view_adjacent,     { .i = -1 } },
    { ClkTagBar,            0,              Button5,        view_adjacent,     { .i = +1 } },

};
