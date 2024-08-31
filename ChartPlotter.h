#ifndef _MLAT_LINE_CHART_HEADER
#define _MLAT_LINE_CHART_HEADER

#include <TFT_eSPI.h> // Hardware-specific library
#include <GUIslice.h>

#define LTBLUE    0xB6DF
#define LTTEAL    0xBF5F
#define LTGREEN   0xBFF7
#define LTCYAN    0xC7FF
#define LTRED     0xFD34
#define LTMAGENTA 0xFD5F
#define LTYELLOW  0xFFF8
#define LTORANGE  0xFE73
#define LTPINK    0xFDDF
#define LTPURPLE  0xCCFF
#define LTGREY    0xE71C
#define BLUE      0x001F
#define TEAL      0x0438
#define GREEN     0x07E0
#define CYAN      0x07FF
#define RED       0xF800
#define MAGENTA   0xF81F
#define YELLOW    0xFFE0
#define ORANGE    0xFC00
#define PINK      0xF81F
#define PURPLE    0x8010
#define GREY      0xC618
#define WHITE     0xFFFF
#define BLACK     0x0000

#define DKBLUE    0x000D
#define DKTEAL    0x020C
#define DKGREEN   0x03E0
#define DKCYAN    0x03EF
#define DKRED     0x6000
#define DKMAGENTA 0x8008
#define DKYELLOW  0x8400
#define DKORANGE  0x8200
#define DKPINK    0x9009
#define DKPURPLE  0x4010
#define DKGREY    0x4A49
 #define CHART_MARGIN 30

class LineChart
{

  public:
  LineChart()
  {
      title=NULL;
      xlabel=NULL;
      ylabel=NULL;      
  };
   LineChart(gslc_tsGui* pGui,gslc_tsElemRef* pElemRef)
   {
      InitObject(pGui,pElemRef);
   }
   void InitObject(gslc_tsGui* pGui,gslc_tsElemRef* pElemRef)
  {
      title=NULL;
      xlabel=NULL;
      ylabel=NULL;   
      rect=gslc_ElemGetRect(pGui,pElemRef);
      p_tft = (TFT_eSPI*)gslc_GetDriverDisp(pGui);
      gx=rect.x+CHART_MARGIN;
      gy=rect.y+rect.h-CHART_MARGIN;
      w=rect.w-CHART_MARGIN*2;
      h=rect.h-CHART_MARGIN ;
     if (!title)  title=new char[20];
     if (!xlabel) xlabel=new char[20];
     if (!ylabel) ylabel=new char[20];
     memset(title,0,20);
     memset(xlabel,0,20);
     memset(ylabel,0,20);
     
     ox=-999;
     oy=-999;
     xlo=0;
     xhi=0;
  }
 ~LineChart()
 {
   if (title) 
   {
     delete title;
     title=NULL;
   }
   if (xlabel)
   {
     delete xlabel;
     xlabel=NULL;
   }
   if (ylabel)
   {
     delete ylabel;
     ylabel=NULL;
   }
 }
 void Clear()
 {
    if (p_tft)
    {
        p_tft->fillRect(rect.x,rect.y,rect.w,rect.h,TFT_BLACK);
    }
    MinPeakY=9999999;
    MaxPeakY=-9999999;
 }
 void MarkPeakMin();
 void GraphFrame(double xlo, double xhi, double xinc,
                 double ylo, double yhi, double yinc,
                 char *title0, char *xlabel0, char *ylabel0);

void UpdateTrace(double x,  double y, bool &update1, unsigned int color);
void DrawGrid();
private:
  TFT_eSPI  *p_tft;
  gslc_tsRect rect;
  double gx,gy,w,h;

  double xlo;
  double xhi;
  double xinc;
  double ylo;
  double yhi;
  double yinc;
  uint8_t x_dot,y_dot;
  double MinPeakY,MinPeakX;
  double MaxPeakX,MaxPeakY;
  
  char *title=NULL;
  char *xlabel=NULL; 
  char *ylabel=NULL;
  double ox = -999, oy = -999; // Force them to be off screen

};

void LineChart::DrawGrid()
{
  unsigned int gcolor = DKBLUE;
  unsigned int acolor = YELLOW;
  unsigned int tcolor = WHITE;
  unsigned int bcolor = BLACK;
 
  double i;
  double temp;

    p_tft->setTextDatum(MR_DATUM);

    // draw y scale
    for ( i = ylo; i <= yhi; i += yinc) {
      // compute the transform
      temp =  (i - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
      p_tft->drawLine(gx, temp, gx + w, temp, gcolor);

      if (i == ylo) {
        p_tft->setTextColor(acolor, bcolor);
        p_tft->drawString(xlabel, (int)(gx + w) , (int)temp, 1);
      }
      // draw the axis labels
      p_tft->setTextColor(tcolor, bcolor);
      // precision is default Arduino--this could really use some format control
      p_tft->drawFloat(i, y_dot, gx - 4, temp, 1);
    }

    // draw x scale
    for (i = xlo; i <= xhi; i += xinc) {

      // compute the transform
      temp =  (i - xlo) * ( w) / (xhi - xlo) + gx;
      if (i == xlo) {
        p_tft->setTextColor(acolor, bcolor);
        p_tft->setTextDatum(BC_DATUM);
        p_tft->drawString(ylabel, (int)temp, (int)(gy - h - 8) , 1);
      }
      p_tft->drawLine(temp, gy, temp, gy - h, gcolor);

      // draw the axis labels
      p_tft->setTextColor(tcolor, bcolor);
      p_tft->setTextDatum(TC_DATUM);
      // precision is default Arduino--this could really use some format control
      p_tft->drawFloat(i, x_dot, temp, gy + 7, 1);
    }

    //now draw the graph labels
    //p_tft->setTextColor(tcolor, bcolor);
    //p_tft->drawString(title, (int)(gx + w / 2) , (int)(gy - h - 30), 4);
    SetChartTitle(title);
}

void LineChart::MarkPeakMin()
{
  double x =  (MinPeakX - xlo) * ( w) / (xhi - xlo) + gx;
  double y =  (MinPeakY - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
  if ((x < gx) || (x > gx+w)) { return;}
  if ((y < gy-h) || (y > gy)) { return;}
  double x1,y1;
  double x2,y2;
  x1=x-2;y1=y+3;
  x2=x+2;y2=y+3;

  p_tft->drawTriangle( x, y,x1,y1,x2,y2,YELLOW);
  p_tft->setTextColor(YELLOW, BLACK);
  p_tft->setTextDatum(TC_DATUM);
  p_tft->drawFloat(MinPeakX, x_dot, x, y + 7, 1);
}

void LineChart::GraphFrame(double xlo0, double xhi0, double xinc0,
                           double ylo0, double yhi0, double yinc0,
                           char *title0, char *xlabel0, char *ylabel0)
 {
   bool clear_required=false;

  if (xhi!=xhi0) clear_required=true;
  if (xlo!=xlo0) clear_required=true;

  xlo=xlo0;
  xhi=xhi0;
  xinc=xinc0;
  ylo=ylo0;
  yhi=yhi0;
  yinc=yinc0;
  
  if (xinc>1)
    x_dot=0;
  else if (xinc>0.1)
    x_dot=1;
  else if (xinc>0.01)
    x_dot=2;
  else  
    x_dot=3;

  if (yinc>1)
    y_dot=0;
  else if (yinc>0.1)
    y_dot=1;
  else if (yinc>0.01)
    y_dot=2;
 else  
    y_dot=3;   
  
  memcpy(title,title0,strlen(title0));
  memcpy(xlabel,xlabel0,strlen(xlabel0));
  memcpy(ylabel,ylabel0,strlen(ylabel0));

  TFT_eSPI tft=*(p_tft);
  if (clear_required==true)      Clear();
  DrawGrid();

}

void LineChart::UpdateTrace(double x,  double y, bool &update1, unsigned int color)
{
 
  if (y>MaxPeakY) 
  {
      MaxPeakY=y;
      MaxPeakX=x;      
  }
  if (y<MinPeakY)
  {
      MinPeakY=y;
      MinPeakX=x;  
  }  
   
  if (y>yhi)
  {
     y=yhi;
    // DrawGrid();
  }
  
  unsigned int pcolor = color;      // pcolor = color of your plotted data
  TFT_eSPI tft=*(p_tft);
  // initialize old x and old y in order to draw the first point of the graph
  // but save the transformed value
  // note my transform funcition is the same as the map function, except the map uses long and we need doubles
  if (update1) {
    update1 = false;
    
    ox = (x - xlo) * ( w) / (xhi - xlo) + gx;
    oy = (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;

    if ((ox < gx) || (ox > gx+w)) {update1 = true; return;}
    if ((oy < gy-h) || (oy > gy)) {update1 = true; return;}
    
    DrawGrid();

  }
  // the coordinates are now drawn, plot the data
  // the entire plotting code are these few lines...
  // recall that ox and oy are initialized above
  x =  (x - xlo) * ( w) / (xhi - xlo) + gx;
  y =  (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
  if ((x < gx) || (x > gx+w)) {update1 = true; return;}
  if ((y < gy-h) || (y > gy)) {update1 = true; return;}
    
  tft.drawLine(ox, oy, x, y, pcolor);
  // it's up to you but drawing 2 more lines to give the graph some thickness
  //tft.drawLine(ox, oy + 1, x, y + 1, pcolor);
  //tft.drawLine(ox, oy - 1, x, y - 1, pcolor);
  ox = x;
  oy = y;

}
#endif
