int preimageSizeFZF(long k) {
    long guess = k * 4, lower_bound_zeroes = 0, diff = 0;
    // count the number of trailing zeroes in the factorial
    // of the initial guess
    while (guess > 0) {
        guess /= 5;
        lower_bound_zeroes += guess;
    }

    // find the difference between k and the lower bound
    // number of trailing zeroes
    if (lower_bound_zeroes < k) {
        diff = k - lower_bound_zeroes;
    } else {
        return 5;
    }

    // compute an upper bound for the number, m > 4k,
    // of trailing zeroes in factorials n!
    int upper_bound_zeroes = k + 1;
    while (upper_bound_zeroes > k) {
        guess = k * 4 + diff * 5; // update guess
        upper_bound_zeroes = 0;
        while (guess > 0) { // recount number of zeroes
            guess /= 5;
            upper_bound_zeroes += guess;
        }
        
        // check upper_bound_zeroes
        if (upper_bound_zeroes > k) {
            --diff;
        } else if (upper_bound_zeroes == k) {
            return 5;
        }
    }

    return 0; // no factorial with k trailing zeroes
}