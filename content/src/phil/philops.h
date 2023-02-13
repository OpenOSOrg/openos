// state of philosophers
enum pstate_e {
      HUNGRY = 1,
      EATING = 2,
      THINKING = 0
};


#define NUM_PHIL 10
extern void take_chopsticks(int p);
extern void put_chopsticks(int p);

extern void init_phil();
extern enum pstate_e get_status_phil(int p);
