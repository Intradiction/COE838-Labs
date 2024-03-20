#include "jkff.h"

void jkff::jkff_method() {
    int newq = Q.read(); // Q(t+1), by default set to Q, change if required
    if(!Q.read() && J.read()){ 
        newq = 1;
    } else if (Q.read() && K.read()){ 
        newq = 0;
    }

    Q.write(newq);
    QP.write(!newq);    
    // Note: CANNOT do QP.write(Q.read()) because they occur concurrently! 
    // You would be reading the old value of Q before it was written to in this clk cycle.
}