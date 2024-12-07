 #ifndef TARDHEAD
 #define TARDHEAD
 #include <Arduino.h>

 #define ZERO  0b00111111
 #define ONE   0b00000110
 #define TWO   0b01011011
 #define THREE 0b01001111
 #define FOUR  0b01100110
 #define FIVE  0b01101101
 #define SIX   0b01111101
 #define SEVEN 0b00000111
 #define AIGHT 0b01111111
 #define NINE  0b01101111
 #define A_SYM     ZERO
 #define B_SYM     0b01111100
 #define C_SYM     0b00111001
 #define D_SYM     0b01011110
 #define E_SYM     0b01111001
 #define F_SYM     0b01110001
 #define G_SYM     0b01101111
 #define H_SYM     0b01110100
 #define I_SYM     0b00001100
 #define J_SYM     0b00001110
 #define K_SYM     ZERO
 #define L_SYM     0b00111000
 #define M_SYM     ZERO //from 2 disp
 #define N_SYM     0b01010100
 #define O_SYM     0b01011100
 #define P_SYM     0b01110011
 #define Q_SYM     0b01100111
 #define R_SYM     0b01010000
 #define S_SYM     FIVE
 #define T_SYM     0b01111000
 #define U_SYM     0b00111110
 #define V_SYM     0b00011100 // think
 #define W_SYM     ZERO //from 2 disp
 #define X_SYM     ZERO // from 2 disp
 #define Y_SYM     0b01101110
 #define Z_SYM     TWO // IDK
 // ---------------------------------------SPEC SYM-------------------------------
 #define SPEC_OFFSET 128
 // A
 #define A1      0b01011100
 #define A2      0b00010000
 #define N_A1    SPEC_OFFSET+0
 #define N_A2    SPEC_OFFSET+1
 // K
 #define K1      0b01110000
 #define K2      0b00111001
 #define N_K1    SPEC_OFFSET+2
 #define N_K2    SPEC_OFFSET+3
 // M
 #define M1      0b01010100 // little m
 #define M2      0b01010100
 #define N_M1    SPEC_OFFSET+4
 #define N_M2    SPEC_OFFSET+5
 // W
 #define W1      0b00011100
 #define W2      0b00011100
 #define N_W1    SPEC_OFFSET+6
 #define N_W2    SPEC_OFFSET+7
 // X
 #define X1      0b01001100
 #define X2      0b01001000
 #define N_X1    SPEC_OFFSET+8
 #define N_X2    SPEC_OFFSET+9

 #define VOSK1   0b10000000 // |
 #define VOSK2   0b00100000 // .
 #define N_VOSK1 SPEC_OFFSET+10
 #define N_VOSK2 SPEC_OFFSET+11
 #define VOPR    0b10000011 // ?
 #define N_VOPR  SPEC_OFFSET+12
 #define MINUS   0b01000000 // -
 #define N_MINUS SPEC_OFFSET+13
 #define POINT   0b10000000 // .
 #define N_POINT SPEC_OFFSET+14
 #define APOSTR   0b00100000 // '
 #define N_APOSTR SPEC_OFFSET+15
 #define SPACE   0 //
 #define N_SPACE 0

 #define USUAL_EYE         0b01100011
 #define DOWN_EYE          0b01011100
 #define USUAL_EYE         0b01100011
 #define CLOSED_EYE        MINUS
 #define CUTE_EYE          0b00000011
 #define SURPRIZED_EYE     ZERO
 #define CRYING_EYE        0b01110111
 #define LEFT_CRYING_EYE   0b01110011
 #define RIGHT_CRYING_EYE  0b01100111
 #define HAPPY_EYE         0b00100011
 #define CALM_EYE          0b01100010
 #define RIGHT             0b00000010
 #define LEFT              0b00100000
 //#define NONE          0


 #define NO_POINT 0

 #define DISP_ON LOW
 #define DISP_OFF HIGH
 #define SEG_ON HIGH
 #define SEG_OFF LOW

 class Eye
 {
     int emotion;
     int pos;
 public:
     Eye(int);
     int get_pos() const;
     void set_pos(int);
     int get_emotion() const;
     void set_emotion(int);
     void move_right();
     void move_left();
 };

 class Eyes
 {
 public:
     static const int emotion_count = 9;
     static const int frazes_count = 8;
 private:
     int orig_pos[2];

     const char* frazes[frazes_count] {"how are you?","Hello","ha ha!","i'm fine!","i'm believe in you!","you can do it!", "just do it!","you are okay?"};
     const byte sz = 2;
     Eye eyes[2];

 public:
     void draw_face();
     Eyes(int pos1,int pos2);
     void draw_both(float dur);

     void set_emotion(int e_, int count = 2, int ind = 0);
     void move_right();
     void move_left();

     void move_down();
     void Default();
     void e_close(float dur, int count = 2, int ind = 0);

     void e_happy(float dur, int count = 2, int ind = 0);
     void e_calm(float dur, int count = 2, int ind = 0);
     void e_cute(float dur, int count = 2, int ind = 0);
     void e_suprise(float dur, int count = 2, int ind = 0);
     void e_cry(float dur, int count = 2, int ind = 0);

     void e_shake(float dur, int count = 2, int ind = 0);

     void e_right_left(float dur);

     void e_down(float dur, int count = 2, int ind = 0);
     void say_frase(int ind);

     void emotions(int ind, float dur, int count = 2, int eye_ind = 0);

 };

 struct Map
 {
     Map() = delete;
     ~Map() = delete;
     static void init();
     static void free();
     static byte find(int);


 private:
     static byte* mas;
 };


 const byte disp_count = 4-1;
 const byte sym_count = 26;
 const byte seg_count = 8;
 const byte num_count = 10;
 const byte spec_sym_count = 17;
 const byte syms[sym_count] = {A_SYM,B_SYM,C_SYM,D_SYM,E_SYM,F_SYM,G_SYM,H_SYM,I_SYM,J_SYM,K_SYM,L_SYM,M_SYM,N_SYM,O_SYM,P_SYM,Q_SYM,R_SYM,S_SYM,T_SYM,U_SYM,V_SYM,W_SYM,X_SYM,Y_SYM,Z_SYM};
 const byte nums[num_count] = {ZERO,ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, AIGHT, NINE};
 const byte segment[seg_count] = {6,7,8,9,10,11,12,13};
 const byte disp[num_count] = {2,3,4,5};
 const byte spec_sym[spec_sym_count] = {A1,A2,K1,K2,M1,M2,W1,W2,X1,X2,VOSK1,VOSK2,VOPR,MINUS,POINT,SPACE,APOSTR};
 const byte n_spec_sym[spec_sym_count] = {N_A1,N_A2,N_K1,N_K2,N_M1,N_M2,N_W1,N_W2,N_X1,N_X2,N_VOSK1,N_VOSK2,N_VOPR,N_MINUS,N_POINT,N_SPACE,N_APOSTR};


 void on_display(byte i);
 void off_display(byte i);
 void draw_digit(byte flags, byte point);
 unsigned char* parse(const char* str, int& sz);
 void static_draw_numb(int numb, int offset = 0);
 void draw_numb(long numb,int first_pos = disp_count-1);
 void static_draw_str(const char* str,int offset = 0);
 void draw_str(const char* str,float dur,int first_pos = disp_count-1);


 #endif