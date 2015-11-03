
/******************************************************
 *
 * canvasdollarzero - implementation file
 *
 *
 * copyleft (c) IOhannes m zmölnig
 *
 *   2007:forum::für::umläute:2007
 *
 *   institute of electronic music and acoustics (iem)
 *
 * based on iemlib2 
 *   copyright (c) 2000-2006 Thomas Musil, IEM, KUG, Graz/Austria
 *
 ******************************************************
 *
 * license: GNU General Public License v.2 (or later)
 *
 ******************************************************/

#include "iemguts.h"
#include "g_canvas.h"


/* -------------- canvasdollarzero --------------- */
/* -- receives the $0 value of the parent canvas --*/

static t_class *canvasdollarzero_class;

typedef struct _canvasdollarzero
{
  t_object     x_obj;
  t_symbol     *s_dollzero;
} t_canvasdollarzero;

static void canvasdollarzero_bang(t_canvasdollarzero *x)
{
  if(x->s_dollzero)
    outlet_symbol(x->x_obj.ob_outlet, x->s_dollzero);
}

static void *canvasdollarzero_new(t_floatarg f)
{
  t_canvasdollarzero *x = (t_canvasdollarzero *)pd_new(canvasdollarzero_class);

  t_glist *glist=(t_glist *)canvas_getcurrent();
  t_canvas *canvas=(t_canvas*)glist_getcanvas(glist);
  int depth=(int)f;

  if(depth<0)depth=0;
  while(depth && canvas) {
    canvas=canvas->gl_owner;
    depth--;
  }

  x->s_dollzero=0;
  if(canvas) {
    x->s_dollzero = canvas_realizedollar(canvas, gensym("$0"));
  }

  outlet_new(&x->x_obj, &s_symbol);
  return (x);
}

void canvasdollarzero_setup(void)
{
  canvasdollarzero_class = class_new(gensym("canvasdollarzero"), 
                                     (t_newmethod)canvasdollarzero_new, 0, 
                                     sizeof(t_canvasdollarzero), 0, 
                                     A_DEFFLOAT, 0);
  class_addbang(canvasdollarzero_class, (t_method)canvasdollarzero_bang);
}
