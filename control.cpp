// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#include "control.h" // class's header file
#include "window.h" // class's header file
#include "mouse.h" // class's header file

bool IsInAnyMenu(void);

bool getarea(int left,int top,int width,int height)
{
     bool isarea = false;
     if (((mousex>=(left))&&(mousey>=(top)))&&(mousex<=(left+width))&&(mousey<=(top+height)))
     {
       isarea = true;
     }
     return isarea;
}

bool getintersectedarea(int l0,int t0,int w0,int h0,int l1,int t1,int w1,int h1)
{
     bool isarea = false;
     if (((mousex>=(l0))&&(mousey>=(t0)))&&(mousex<=(l0+w0))&&(mousey<=(t0+h0)))
     {
       if ((((mousex>=(l1))&&(mousey>=(t1)))&&(mousex<=(l1+w1))&&(mousey<=(t1+h1))))
       {
         isarea = true;
         return isarea;
       } else 
       {
         isarea = false;
         return isarea;
       }
     }
     return isarea;
}

// class constructor
TControl::TControl()
{
          id=0;
          name="control";
          visible = false;
          left=0;
          top=0;
          width=64;
          height=64;
          alphavalue = 255;
          focus = false;
          clicked = false;
          hint = "";
          showhint = false;
          resethint = false;
          flat = true;
          if (instance == NULL) instance = this;
}

// class destructor
TControl::~TControl()
{
	// insert your code here
}


void TControl::show()
{
          visible = true;
          if (IsInControl(this)) focused = true;
          if (IsInAnyMenu())
          {
              focus = false;
              focused = false;
          }
          if (visible==true) render(this);
          instance = this;
}

bool iscwindow = false;
bool getarea(int left,int top,int width,int height);

bool TControl::IsInControl(TControl* Control)
{
     bool iscontrol = false;
     int wt = Control->window->height-Control->window->clientheight;
     if ((Control->window->borderstyle != bsNone)&&(windowmanager == 1)) wt -= 3;
     
     if (Control->window->freezing) return false;

     if (IsInAnyMenu()) return false;

     if (((mousex>=(Control->window->left+Control->left))&&(mousey>=(Control->window->top+wt+Control->top)))&&(mousex<=(Control->window->left+Control->left+Control->width))&&(mousey<=(Control->window->top+Control->top+wt+Control->height)))
     {
       iscontrol = true;     
       if (Control->window->modalhalt) return false;
       
       for (int i=0;i<numwindows;i++)
       {
        if (windows[i]->visible && Control->window->visible && Control->visible)
        {
          if (i!=Control->window->windowid)
          {
           if (iscontrol)
           {
             if (getarea(windows[i]->left,windows[i]->top,windows[i]->width,windows[i]->height+wt)) iscontrol = false;
           }
          }
        }
       }
       
       if (iscontrol) return true;
     }
     
     int l0=0, t0=0, w0=0, h0=0, l1=0, t1=0, w1=0, h1=0, l2=0, t2=0, w2=0, h2=0, l3=0, t3=0, w3=0, h3=0, l4=0, t4=0, w4=0, h4=0;

     for (int i=0;i<numwindows;i++)
     {
      if (windows[i]->visible && Control->window->visible && Control->visible)
      {
        if (((((mousex>=(windows[i]->left+Control->left))&&(mousey>=(windows[i]->top+wt+Control->top)))&&(mousex<=(windows[i]->left+Control->left+Control->width))&&(mousey<=(windows[i]->top+Control->top+wt+Control->height)))))
        {
          l0 = windows[i]->left+Control->left;
          t0 = windows[i]->top+wt+Control->top;
          w0 = Control->width;
          h0 = wt+Control->height;
        }

        l2 = (l0-l1);
        t2 = (t0-t1);
        w2 = (w0-w1);
        h2 = (h0-h1);
       
        if (windows[i]->visible && Control->window->visible && Control->visible)
        {
           if (Control->window->windowid != i)
           {
             l3 = windows[i]->left;
             t3 = windows[i]->top+wt;
             w3 = windows[i]->width;
             h3 = windows[i]->height;
            // rectangle(l3,t3,l3+w3,t3+h3-wt+3,clRed,255);
           }
           if ((((mousex>=(l2))&&(mousey>=(t2)))&&(mousex<=(l2+w2))&&(mousey<=(t2+h2))))
           {
              if (i != Control->window->windowid) 
              {  
                    if ((((mousex>=(l3))&&(mousey>=(t3)))&&(mousex<=(l3+w3))&&(mousey<=(t3+h3))))
                    {
                       l4 = windows[i]->left;
                       t4 = windows[i]->top;
                       w4 = windows[i]->width;
                       h4 = windows[i]->height;
                       iscwindow = true;
/*
                       l5 = Control->window->left+Control->left;
                       t5 = Control->window->top+wt+Control->top;
                       w5 = Control->width;
                       h5 = Control->height+wt;    
                                      
                       if (getarea(l5,t5,w5,h5))    
                       {
                         return true;
                       }
                       rectangle(l4,t4,l4+w4,t4+h4-wt+3,clRed,255);   
*/               
                    //  return false;
                    } else
                    {/*
                       l4 = 0;
                       t4 = 0;
                       w4 = 0;
                       h4 = 0;*/
                       if (Control->window->windowid!=i) iscwindow = false;
                    }
              }
           }
        }
        if (((((mousex>=(windows[i]->left+Control->left))&&(mousey>=(windows[i]->top+wt+Control->top)))&&(mousex<=(windows[i]->left+Control->left+Control->width))&&(mousey<=(windows[i]->top+wt+Control->top+Control->height)))))
        {
          l1 = windows[i]->left+Control->left;
          t1 = windows[i]->top+wt+Control->top;
          w1 = Control->width;
          h1 = wt+Control->height;        
        }
      }
      }
      l0=0;
      t0=0;
      w0=0;
      h0=0;
      l1=0;
      t1=0;
      w1=0;
      h1=0;
      l2=0;
      t2=0;
      w2=0;
      h2=0;
      l3=0;
      t3=0;
      w3=0;
      h3=0;
      
      int l6=0,t6=0,w6=0,h6=0;
      int cwin = 0;
      int nwin = 0;
      bool r=false;
      for (int i=0;i<numwindows;i++)
      {
          l0 = windows[i]->left;
          t0 = windows[i]->top;
          w0 = windows[i]->width;
          h0 = windows[i]->height;
          if (windows[i]->visible)
          {
            if (getarea(l0,t0,w0,h0))
            {
//              if (i != Control->window->windowid) 
              {
                    l1 = Control->window->left;
                    t1 = Control->window->top;
                    w1 = Control->window->width;
                    h1 = Control->window->height;
                    for (int j=0;j<numwindows;j++) 
                    {
                          if (getarea(l1,t1,w1,h1)) nwin = j;
                    }
              }
            }
          }
      }
//      if (!Control->window->modalhalt)
      {
        for (int i=0;i<numwindows;i++)
        {
          l0 = windows[i]->left;
          t0 = windows[i]->top;
          w0 = windows[i]->width;
          h0 = windows[i]->height;
          if (windows[i]->visible)
          {
            if (getarea(l0,t0,w0,h0))
            {
              if (i != Control->window->windowid) 
              {
                  //  cwin = i;
                    l1 = Control->window->left;
                    t1 = Control->window->top;
                    w1 = Control->window->width;
                    h1 = Control->window->height;
                    for (int j=numwindows-1;j>0;j--) 
                    {
                      if (windows[j]->visible)
                      {
                        if (j != Control->window->windowid)
                        {
                          if (getarea(l1,t1,w1,h1))
                          {
                            if (i != nwin)
                            {
                                   if (nwin>j)
                                   {
                                      l2 = Control->window->left+Control->left;
                                      t2 = Control->window->top+wt+Control->top;
                                      w2 = Control->width;
                                      h2 = Control->height+wt;    
                                      
                                      if (getarea(l2,t2,w2,h2))    
                                      {
                                        if (Control->window->modalhalt==false) cwin = i;
                                        else return false;
                                      }
                                   }
                            }
                            else 
                            {
                                 l2 = windows[j]->left;
                                 t2 = windows[j]->top;
                                 w2 = windows[j]->width;
                                 h2 = windows[j]->height;
                                 if (getarea(l2,t2,w2,h2))
                                 {
                                   if (windows[j]->modalhalt==false) cwin = j;
                                   else return false;
                                 }
                                 //if (j>i) nwin = j-i;
                            }
                          }
                        } else nwin = j;
                      }
                    }
              }
            }
          }
        }
      }
      l0=0;
      t0=0;
      w0=0;
      h0=0;
      l1=0;
      t1=0;
      w1=0;
      h1=0;
      l2=0;
      t2=0;
      w2=0;
      h2=0;
      l3=0;
      t3=0;
      w3=0;
      h3=0;
     for (int i=0;i<numwindows;i++)
     {
      if (windows[i]->visible && Control->window->visible && Control->visible)
      {
        if (((((mousex>=(windows[i]->left+Control->left))&&(mousey>=(windows[i]->top+wt+Control->top)))&&(mousex<=(windows[i]->left+Control->left+Control->width))&&(mousey<=(windows[i]->top+Control->top+wt+Control->height)))))
        {
          l0 = windows[i]->left+Control->left;
          t0 = windows[i]->top+wt+Control->top;
          w0 = Control->width;
          h0 = wt+Control->height;
        }

        l2 = (l0-l1);
        t2 = (t0-t1);
        w2 = (w0-w1);
        h2 = (h0-h1);
        
        if (windows[i]->visible && Control->window->visible && Control->visible)
        {
           if (Control->window->windowid != i)
           {
             l3 = windows[i]->left;
             t3 = windows[i]->top+wt;
             w3 = windows[i]->width;
             h3 = windows[i]->height;
           }
           else
           {
             l6 = windows[i]->left;
             t6 = windows[i]->top+wt;
             w6 = windows[i]->width;
             h6 = windows[i]->height;
           }
           if ((((mousex>=(l2))&&(mousey>=(t2)))&&(mousex<=(l2+w2))&&(mousey<=(t2+h2))))
           {
              //SetWindowText(hWnd,ltoa(cwin));
              {
              }
              if (i == Control->window->windowid) 
              {
                    
                    
                    if (Control->window->modalhalt) return false;
                    int wn = 0;
                    wn = cwin;
                    //if (wn!=i) wn = Control->window->windowid;
//                    if ((((l0>=(l2))&&(t0>=(t2)))&&(l0<=(l2+w2))&&(t0<=(t2+h2)))) return false;
                   // if (windows[i]->IsInWindow(windows[i])) 
                    {
                      if (getarea(Control->window->left,Control->window->top,Control->window->width,Control->window->height))
                      {
                          r= true;
                          l0 = windows[cwin]->left;
                          t0 = windows[cwin]->top;
                          w0 = windows[cwin]->width;
                          h0 = windows[cwin]->height;
                          
                          if (getarea(l0,t0,w0,h0)&&(cwin==activewindow)) r = false;
                          //if (!(getarea(l0,t0,w0,h0)&&(cwin!=activewindow))) r = false;
                      }
                     // else return false;
                    }
                 //   else 
                    {
                   //   if (!getarea(l4,t4+wt+3,w4,h4)) r= false;
                  //    else r= true;
                    }
                    return r;
                    //if (Control->window->IsInWindow(windows[wn])) return true;
              }
              else
              {
                  if (i != activewindow)
                  {
                      if (getarea(Control->window->left,Control->window->top,Control->window->width,Control->window->height))
                      {
                          if (Control->window->modalhalt) return false;
                          if (getarea(Control->window->left+Control->left,Control->window->top+wt+Control->top,Control->width,Control->height+wt)) return true;
                          l0 = windows[cwin]->left;
                          t0 = windows[cwin]->top;
                          w0 = windows[cwin]->width;
                          h0 = windows[cwin]->height;
                        //  if (getarea(l0,t0,w0,h0)&&(cwin==activewindow)) r = false;
                          //if (!(getarea(l0,t0,w0,h0)&&(cwin!=activewindow))) r = false;
                      }
                  }
              }
          }
        }
        if (((((mousex>=(windows[i]->left+Control->left))&&(mousey>=(windows[i]->top+wt+Control->top)))&&(mousex<=(windows[i]->left+Control->left+Control->width))&&(mousey<=(windows[i]->top+wt+Control->top+Control->height)))))
        {
          l1 = windows[i]->left+Control->left;
          t1 = windows[i]->top+wt+Control->top;
          w1 = Control->width;
          h1 = wt+Control->height;        
        }
      }
     }


     if (Control->window->modalhalt) iscontrol = false;
     return iscontrol;
}

