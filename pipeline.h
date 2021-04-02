
/*
 * 
 * pipeline.h
 * 
 */

#define TRUE 1
#define FALSE 0

#define INT_DEST_AT_2 1
#define INT_DEST_AT_3 2
#define FP_DEST_AT_2 3
#define FP_DEST_AT_3 4

#define INT_SOURCE_ONE 1
#define INT_SOURCE_TWO 2
#define FP_SOURCE_ONE 3
#define FP_SOURCE_TWO 4
#define BOTH_SOURCE 5


/* fetch/decode pipeline register */
typedef struct _if_id_t {
  int instr;
  unsigned long pc;
} if_id_t;


/* Register state */
typedef struct _rf_int_t {
  int_t reg_int[NUMREGS];
} rf_int_t;

typedef struct _rf_fp_t {
  float reg_fp[NUMREGS];
} rf_fp_t;


/* Overall processor state */
typedef struct _state_t {
  /* memory */
  unsigned char mem[MAXMEMORY];

  /* register files */
  rf_int_t rf_int;
  rf_fp_t rf_fp;

  /* pipeline registers */
  unsigned long pc;
  if_id_t if_id;

  fu_int_t *fu_int_list;
  fu_fp_t *fu_add_list;
  fu_fp_t *fu_mult_list;
  fu_fp_t *fu_div_list;

  wb_t int_wb;
  wb_t fp_wb;

  int fetch_lock;

  int control_stall;
  int stalled_inst; 
  int stall_counter;
  int halt_activated;
  int end_simulation;
  
} state_t;

extern state_t *state_create(int *, FILE *, FILE *);

extern void writeback(state_t *, int *);
extern void execute(state_t *);
extern int decode(state_t *);
extern void fetch(state_t *);
