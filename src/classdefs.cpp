#include "Header.hpp"

byte* Map::mas = new byte[256];
// Eye
Eye::Eye(int pos_) : emotion{USUAL_EYE}, pos{pos_}
{
}
int Eye::get_pos() const {
    return pos;
}
void Eye::set_pos(int p_) {
    pos = p_;
}
int Eye::get_emotion() const {
    return emotion;
}
void Eye::set_emotion(int e_) {
    emotion = e_;
}
void Eye::move_right()
{
    pos++;
}
void Eye::move_left()
{
    pos++;
}


// Map

void Map::init()
{
    for(int i = 0; i < num_count; i++)
    {
        mas[i] = nums[i];
    }
    for(int i = '0', j = 0; i <= '9'; i++,j++)
    {
        mas[i] = nums[j];
    }
    for(int i = 'a', j = 0; i < 'a'+sym_count-1; i++,j++)
    {
        mas[i] = syms[j];
    }
    for(int i = 'A', j = 0; i < 'A'+sym_count-1; i++,j++)
    {
        mas[i] = syms[j];
    }
    for(int i = 0; i < spec_sym_count; i++) {
        mas[n_spec_sym[i]] = spec_sym[i];
    }
}

byte Map::find(int i) {
  return mas[i];
}


void Map::free()
{
    delete[] mas;
}

//  Eyes

Eyes::Eyes(int pos1,int pos2) : eyes{ Eye(pos1), Eye(pos2)}, orig_pos{pos1,pos2}
  {
  }

  void Eyes::draw_both(float dur)
{
  long now = millis();
  while(millis() - now < dur*1000) {
    for (int i = 0; i < sz; i++) {
        if (eyes[i].get_pos() >= 0 && eyes[i].get_pos() < disp_count) {
            draw_digit(eyes[i].get_emotion(), NO_POINT);
            on_display(eyes[i].get_pos());
            delay(1);
            off_display(eyes[i].get_pos());
        }
    }
  }
}

void Eyes::set_emotion(int e_, int count, int ind) {
    if (count < 2) {
        eyes[ind].set_emotion(e_ == CRYING_EYE ? (ind == 0 ? LEFT_CRYING_EYE : RIGHT_CRYING_EYE) : e_);
        return;
    }
    for (int ind = 0; ind < count; ind++)
        eyes[ind].set_emotion(e_ == CRYING_EYE ? (ind == 0 ? LEFT_CRYING_EYE : RIGHT_CRYING_EYE) : e_);
}

void Eyes::move_right()
{
    for (int i = 0; i < sz; i++)
        eyes[i].move_right();
}
void Eyes::move_left()
{
    for (int i = 0; i < sz; i++)
        eyes[i].move_left();
}

void Eyes::move_down()
{
     set_emotion(DOWN_EYE, 2);
}

void Eyes::Default()
{
    set_emotion(USUAL_EYE, 2);
    for (int i = 0; i < sz; i++)
        eyes[i].set_pos(orig_pos[i]);
}
void Eyes::e_close(float dur, int count, int ind)
{
    set_emotion(CLOSED_EYE, count,ind);
    draw_both(dur);

}

void Eyes::e_happy(float dur, int count, int ind)
{
    set_emotion(HAPPY_EYE, count,ind);
    draw_both(dur);
}
void Eyes::e_calm(float dur, int count, int ind)
{
    set_emotion(CALM_EYE, count,ind);
    draw_both(dur);
}
void Eyes::e_cute(float dur, int count, int ind)
{
    set_emotion(CUTE_EYE, count,ind);
    draw_both(dur);

}
void Eyes::e_suprise(float dur, int count, int ind)
{
    set_emotion(SURPRIZED_EYE, count,ind);
    draw_both(dur);

}
void Eyes::e_cry(float dur, int count, int ind)
{
    set_emotion(CRYING_EYE, count,ind);
    draw_both(dur);

}

void Eyes::e_shake(float dur, int count, int ind)
{
    move_down();
    draw_both(dur / 4.f);

    move_right();
    draw_both(dur / 4.f);

    move_left();
    move_left();
    draw_both(dur / 4.f);

    move_right();
    draw_both(dur / 4.f);

    Default();
    draw_both(dur / 4.f);

}

void Eyes::e_right_left(float dur)
{

    set_emotion(RIGHT);
    draw_both(dur);

    set_emotion(LEFT);
    draw_both(dur);

    set_emotion(RIGHT);
    draw_both(dur);
}

void Eyes::e_down(float dur, int count, int ind)
{
    set_emotion(DOWN_EYE, count,ind);
    draw_both(dur);

}

  void Eyes::say_frase(int ind) {
    draw_str(frazes[ind],0.5);
  }

void Eyes::emotions(int ind, float dur, int count, int eye_ind)
{
  switch(ind) {
    case 8:
      e_down(dur,count,eye_ind);
      break;
    case 7:
      e_right_left(dur);
      break;
    case 6:
      e_shake(dur,count,eye_ind);
      break;
    case 5:
      e_cry(dur,count,eye_ind);
      break;
    case 4:
      e_suprise(dur);
      break;
    case 3:
      e_cute(dur,count,eye_ind);
      break;
    case 2:
      e_calm(dur);
      break;
    case 1:
      e_happy(dur);
      break;
    case 0:
      e_close(dur,count,eye_ind);
      break;

  }
  }

void on_display(byte i)
{
  digitalWrite(disp[i],DISP_ON);
}

void off_display(byte i)
{
  digitalWrite(disp[i],DISP_OFF);
}

void draw_digit(byte flags, byte point)
{
  flags |= point;
  for(byte i = 0; i < seg_count; i++) {
    digitalWrite(segment[i],bitRead(flags,i) == 1? SEG_ON : SEG_OFF);
  }
}

unsigned char* parse(const char* str, int& sz) {
  int count = 0;
  for(const char* temp_it = str; *temp_it != '\0'; temp_it++)
  {
    count++;
  }
  unsigned char* buff = new unsigned char[count*2];
  unsigned char* it = buff;
  sz = 0;
  for(const char* temp_it = str; *temp_it != '\0'; temp_it++,it++,sz++) {
    switch (*temp_it)
    {
      case 'a':
      case 'A':
        *it = N_A1;
      sz++;
      it++;
      *it = N_A2;
      break;
      case 'k':
      case 'K':
        *it = N_K1;
      it++;
      sz++;
      *it = N_K2;
      break;
      case 'm':
      case 'M':
        *it = N_M1;
      it++;
      sz++;
      *it = N_M2;
      break;
      case 'w':
      case 'W':
        *it = N_W1;
      it++;
      sz++;
      *it = N_W2;
      break;
      case 'x':
      case 'X':
        *it = N_X1;
      it++;
      sz++;
      *it = N_X2;
      break;
      case '!':
        *it = N_VOSK1;
      it++;
      sz++;
      *it = N_VOSK2;

      break;
      case '?':
        *it = N_VOPR;
      break;
      case '-':
        *it = N_MINUS;
      break;
      case '.':
        *it = N_POINT;
      break;
      case ' ':
        *it = N_SPACE;
      break;
      case '\'':
        *it = N_APOSTR;
      break;

      default:
        *it = *temp_it;
      break;
    }

  }
  *it = '\0';
  return buff;
}

void static_draw_numb(int numb, int offset)
{
  byte i = disp_count-1;
  while(numb != 0)
  {
    byte digit = numb%10;

    draw_digit(Map::find(digit),NO_POINT);
    if(i-offset >= 0)
      on_display(i-offset);

    numb /= 10;
    delay(10);

    if(i-offset >= 0)
      off_display(i-offset);

    i--;
  }
}

void draw_numb(long numb,int first_pos)
{

  int numb_offset = 0;    //index of last digit in number, where first digit has index 1
  if(numb == 0)
    numb_offset++;

  long temp = numb;
  while(temp != 0) {
    numb_offset++;
    temp /= 10;
  }
  int count = numb_offset;
  while (numb_offset != -1 * disp_count)
  {
    int temp_offset = numb_offset;
    long temp_numb = numb;
    int temp_count = count;
    while(temp_count > 0)
    {
      byte digit = temp_numb%10;
      int ind = first_pos + temp_offset;

      if(ind >= 0 && ind < disp_count) {
        draw_digit(Map::find(digit),NO_POINT);
        on_display(ind);
        delay(1);
        off_display(ind);
      }
      else
        delay(1);

      temp_numb /= 10;
      temp_offset--;
      temp_count--;
    }
    if(millis()%50 == 0)
      numb_offset--;
  }
}

void static_draw_str(const char* str,int offset ) {
  int sz = 0;
  unsigned char* buff = parse(str,sz);
  int off = 0;
  byte i = disp_count-1;
  while(*buff != 0)
  {
    byte digit = *(buff+off);

    draw_digit(Map::find(digit),NO_POINT);
    if(i-offset >= 0)
      on_display(i-offset);

    off++;
    delay(10);

    if(i-offset >= 0)
      off_display(i-offset);

    i--;
  }
  delete[] buff;
}

void draw_str(const char* str,float dur,int first_pos)
{
  int pos_last_sym = 0;
  unsigned char* buff = parse(str,pos_last_sym);
  unsigned char* last_sym_it = buff+pos_last_sym-1;

  const int count = pos_last_sym;
  while (pos_last_sym != -1 * disp_count) // while last symbol won't turn out of screen, gradually decrease it by 1
  {
    static long now = millis();
    int pos_curr_sym = pos_last_sym; // pos of last digit into number, moving from left to right
    unsigned char* curr_sym_it = last_sym_it;
    int temp_count = count;     // count of digits which drawing or should be drawed

    while(temp_count > 0) {
      unsigned char sym = *curr_sym_it;
      int ind = first_pos + pos_curr_sym; // index of display which should draw sym

      if(ind >= 0 && ind < disp_count) {
        draw_digit(Map::find(sym),NO_POINT);
        on_display(ind);
        delay(1);
        off_display(ind);
      }
      delay(1);

      curr_sym_it--;
      pos_curr_sym--;
      temp_count--;
    }

    if(millis() - now > (unsigned long)(dur*1000)) {
      pos_last_sym--;
      now = millis();
    }
  }
  delete[] buff;
}
void Eyes::draw_face()
{
  while(1) {
    int r = random(0,7);
    Default();
    draw_both(1);
    static int last = millis();
    if(millis() - last >= 3*1000) {

      if(r >= 0 && r <= 3) {
        e_close(1);
        r = random(1,8);
      }
      else if(r >= 4 && r <= 5){
        emotions(random(1,Eyes::emotion_count),random(7,20)*1.f/10.f, random(1,3),random(0,2));
      }
      else
        say_frase(random(0,frazes_count));
      last = millis();
    }
  }
}