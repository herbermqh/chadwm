/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int default_border = 0;   /* to switch back to default border after dynamic border resizing via keybinds */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails,display systray on the 1st monitor,False: display systray on last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int showtab            = showtab_auto;
static const int toptab             = 1;        /* 0 means bottom tab */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int horizpadbar        = 5;
static const int vertpadbar         = 11;
static const int vertpadtab         = 33;
static const int horizpadtabi       = 15;
static const int horizpadtabo       = 15;
static const int scalepreview       = 4;
static const int tag_preview        = 1;        /* 1 means enable, 0 is off */
static const int colorfultag        = 1;        /* 0 means use SchemeSel for selected non vacant tag */


static const char *fonts[]          = { "Hack Nerd Font:size=10",
                                        "Hack Nerd Font:size=15",
                                      };

// theme
#include "themes/hdark.h"

static const char *colors[][3]      = {
    /*                     fg       bg      border */
    [SchemeNorm]       = { gray3,   black,  gray2 },
    [SchemeSel]        = { gray4,   blue,   blue  },
    [TabSel]           = { blue,    gray2,  black },
    [TabNorm]          = { gray3,   black,  black },
    [SchemeTag]        = { gray3,   black,  black },
    [SchemeTag1]       = { blue,    black,  black },
    [SchemeTag2]       = { red,     black,  black },
    [SchemeTag3]       = { orange,  black,  black },
    [SchemeTag4]       = { green,   black,  black },
    [SchemeTag5]       = { pink,    black,  black },
    [SchemeLayout]     = { green,   black,  black },
    [SchemeBtnPrev]    = { green,   black,  black },
    [SchemeBtnNext]    = { yellow,  black,  black },
    [SchemeBtnClose]   = { red,     black,  black },
};

/* tagging */
static char *tags[] = {"  ", " {} ", "  ", "  ", "  "};



static const char* eww[] = { "eww", "open" , "eww", NULL };

static const Launcher launchers[] = {
    /* command     name to display */
    { eww,         " " },
};

static const int tagschemes[] = {
    SchemeTag1, SchemeTag2, SchemeTag3, SchemeTag4, SchemeTag5
};

static const unsigned int ulinepad      = 5; /* horizontal padding between the underline and tag */
static const unsigned int ulinestroke   = 2; /* thickness / height of the underline */
static const unsigned int ulinevoffset  = 0; /* how far above the bottom of the bar the line should appear */
static const int ulineall               = 0; /* 1 to show underline on all tags, 0 for just the active ones */

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     iscentered   isfloating   monitor */
    { "Gimp",     NULL,       NULL,       0,            0,           1,           -1 },
    { "Firefox",  NULL,       NULL,       1 << 8,       0,           0,           -1 },
    { "eww",      NULL,       NULL,       0,            0,           1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "functions.h"


static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[]=",      tile },    /* first entry is default */
    { "[M]",      monocle },
    { "[@]",      spiral },
    { "[\\]",     dwindle },
    { "H[]",      deck },
    { "TTT",      bstack },
    { "===",      bstackhoriz },
    { "HHH",      grid },
    { "###",      nrowgrid },
    { "---",      horizgrid },
    { ":::",      gaplessgrid },
    { "|M|",      centeredmaster },
    { ">M>",      centeredfloatingmaster },
    { "><>",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define M Mod4Mask
#define S ShiftMask
#define C ControlMask
#define TAGKEYS(KEY,TAG) \
{ M,                       KEY,      view,           {.ui = 1 << TAG} }, \
{ M|M,                KEY,      toggleview,     {.ui = 1 << TAG} }, \
{ M|S,                KEY,      tag,            {.ui = 1 << TAG} }, \
{ M|M|S,              KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */

static Key keys[] = {
  /* modifier                         key         function        argument */

  // brightness and audio 
  {0,                     XF86XK_AudioMute,       spawn,          SHCMD("pamixer -t")},
  {0,              XF86XK_AudioRaiseVolume,       spawn,          SHCMD("pamixer -i 1")},
  {0,              XF86XK_AudioLowerVolume,       spawn,          SHCMD("pamixer -d 1")},
  {0,              XF86XK_MonBrightnessDown,      spawn,          SHCMD("xbacklight -dec 1")},
  {0,              XF86XK_MonBrightnessUp,        spawn,          SHCMD("xbacklight -inc 1")},

  /* screenshot */
  {0,             XK_Print,                       spawn,          SHCMD("flameshot gui -d 0")},

  /* // screenshot fullscreen and cropped */
  /* {M|M,                XK_u,       spawn, */
  /*   SHCMD("maim | xclip -selection clipboard -t image/png")}, */
  /* {M,                            XK_u,       spawn, */
  /*   SHCMD("maim --select | xclip -selection clipboard -t image/png")}, */



  /* { M,                           XK_p,       spawn,          SHCMD("rofi -show drun") }, */
  { M,                           XK_p,       spawn,          SHCMD("sh /home/userh/.config/rofi/launchers/misc/launcher.sh") },
  { M,                           XK_Return,  spawn,          SHCMD("alacritty")},
  // { M,                       XK_Return, spawn,            SHCMD("st_pad && st")},


  // toggle stuff
  { M,                            XK_b,       togglebar,      {0} },
  { M|M,                          XK_t,       togglegaps,     {0} },
  { M|S,                          XK_space,   togglefloating, {0} },
  { M,                            XK_f,       togglefullscr,  {0} },

  { M|M,                          XK_w,       tabmode,        { -1 } },
  { M,                            XK_j,       focusstack,     {.i = +1 } },
  { M,                            XK_k,       focusstack,     {.i = -1 } },
  { M,                            XK_i,       incnmaster,     {.i = +1 } },
  { M,                            XK_d,       incnmaster,     {.i = -1 } },

  // change m,cfact sizes
  { M,                          XK_h,       setmfact,       {.f = -0.05} },
  { M,                          XK_l,       setmfact,       {.f = +0.05} },
  { M|S,                        XK_h,       setcfact,       {.f = +0.25} },
  { M|S,                        XK_l,       setcfact,       {.f = -0.25} },
  { M|S,                        XK_o,       setcfact,       {.f =  0.00} },


  { M|S,                  XK_j,       movestack,      {.i = +1 } },
  { M|S,                  XK_k,       movestack,      {.i = -1 } },
  { M|S,                  XK_Return,  zoom,           {0} },
  { M,                    XK_Tab,     view,           {0} },

  // overall gaps
  { M|M,               XK_i,       incrgaps,       {.i = +1 } },
  { M|M,               XK_d,       incrgaps,       {.i = -1 } },

  // inner gaps
  { M|S,                  XK_i,       incrigaps,      {.i = +1 } },
  { M|M|S,                XK_i,       incrigaps,      {.i = -1 } },

  // outer gaps
  { M|M,                XK_o,       incrogaps,      {.i = +1 } },
  { M|M|S,              XK_o,       incrogaps,      {.i = -1 } },

  // inner+outer hori, vert gaps 
  { M|M,                XK_6,       incrihgaps,     {.i = +1 } },
  { M|M|S,              XK_6,       incrihgaps,     {.i = -1 } },
  { M|M,                XK_7,       incrivgaps,     {.i = +1 } },
  { M|M|S,              XK_7,       incrivgaps,     {.i = -1 } },
  { M|M,                XK_8,       incrohgaps,     {.i = +1 } },
  { M|M|S,              XK_8,       incrohgaps,     {.i = -1 } },
  { M|M,                XK_9,       incrovgaps,     {.i = +1 } },
  { M|M|S,              XK_9,       incrovgaps,     {.i = -1 } },
  { M|M|S,              XK_d,       defaultgaps,    {0} },


  // layout
  { M,                  XK_t,       setlayout,      {.v = &layouts[0]} },
  { M|S,                XK_f,       setlayout,      {.v = &layouts[1]} },
  { M,                  XK_m,       setlayout,      {.v = &layouts[2]} },
  { M|M,                XK_g,       setlayout,      {.v = &layouts[10]} },
  { M|M|S,              XK_t,       setlayout,      {.v = &layouts[13]} },
  { M,                  XK_space,   setlayout,      {0} },
  { M|M,                XK_comma,   cyclelayout,    {.i = -1 } },
  { M|M,                XK_period,  cyclelayout,    {.i = +1 } },
  { M,                  XK_0,       view,           {.ui = ~0 } },
  { M|S,                XK_0,       tag,            {.ui = ~0 } },
  { M,                           XK_comma,   focusmon,       {.i = -1 } },
  { M,                           XK_period,  focusmon,       {.i = +1 } },
  { M|S,                 XK_comma,   tagmon,         {.i = -1 } },
  { M|S,                 XK_period,  tagmon,         {.i = +1 } },

  // change border size
  { M|S,                 XK_minus,   setborderpx,    {.i = -1 } },
  { M|S,                 XK_p,       setborderpx,    {.i = +1 } },
  { M|S,                 XK_w,       setborderpx,    {.i = default_border } },

  // kill dwm
  { M|C,               XK_q,       quit,           {0} },

  // kill window
  { M,                           XK_q,       killclient,     {0} },

  // restart
  { M|S,                 XK_r,       quit,           {1} },

  // hide & restore windows
  { M,                           XK_e,       hidewin,        {0} },
  { M|S,                 XK_e,       restorewin,     {0} },

  TAGKEYS(                            XK_1,                       0)
    TAGKEYS(                            XK_2,                       1)
    TAGKEYS(                            XK_3,                       2)
    TAGKEYS(                            XK_4,                       3)
    TAGKEYS(                            XK_5,                       4)
    TAGKEYS(                            XK_6,                       5)
    TAGKEYS(                            XK_7,                       6)
    TAGKEYS(                            XK_8,                       7)
    TAGKEYS(                            XK_9,                       8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
  /* click                event mask      button          function        argument */
  { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
  { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
  { ClkWinTitle,          0,              Button2,        zoom,           {0} },
  { ClkStatusText,        0,              Button2,        spawn,          SHCMD("alacritty") },

  /* Keep movemouse? */
  /* { ClkClientWin,         M,         Button1,        movemouse,      {0} }, */

  /* placemouse options, choose which feels more natural:
   *    0 - tiled position is relative to mouse cursor
   *    1 - tiled postiion is relative to window center
   *    2 - mouse pointer warps to window center
   *
   * The moveorplace uses movemouse or placemouse depending on the floating state
   * of the selected client. Set up individual keybindings for the two if you want
   * to control these separately (i.e. to retain the feature to move a tiled window
   * into a floating position).
   */
  { ClkClientWin,         M,         Button1,        moveorplace,    {.i = 0} },
  { ClkClientWin,         M,         Button2,        togglefloating, {0} },
  { ClkClientWin,         M,         Button3,        resizemouse,    {0} },
  { ClkClientWin,         M,    Button1,        dragmfact,      {0} },
  { ClkClientWin,         M,    Button3,        dragcfact,      {0} },
  { ClkTagBar,            0,              Button1,        view,           {0} },
  { ClkTagBar,            0,              Button3,        toggleview,     {0} },
  { ClkTagBar,            M,         Button1,        tag,            {0} },
  { ClkTagBar,            M,         Button3,        toggletag,      {0} },
  { ClkTabBar,            0,              Button1,        focuswin,       {0} },
  { ClkTabBar,            0,              Button1,        focuswin,       {0} },
  { ClkTabPrev,           0,              Button1,        movestack,      { .i = -1 } },
  { ClkTabNext,           0,              Button1,        movestack,      { .i = +1 } },
  { ClkTabClose,          0,              Button1,        killclient,     {0} },
};
