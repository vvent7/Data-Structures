// most significant bit index
int msbi(int x);

// smallest k:  2^k >= x
int first_power_of_2(int x);

// 2 ^ ceil(log(first_power_of_2(x))/2)
int upper_sqrt(int x);

// 2 ^ floor(log(first_power_of_2(x))/2)
int lower_sqrt(int x);