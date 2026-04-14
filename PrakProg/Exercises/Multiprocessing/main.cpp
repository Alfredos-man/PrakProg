#include <iostream>
#include <thread>
#include <vector>
#include <string>

struct dataa {
    long long a, b;
    double sum;
};

void harm(dataa& arg) {
    long long a = arg.a, b = arg.b;
    double sum = 0.0;

    for (long long i = a; i < b; i++) {
        sum += 1.0 / i;
    }

    arg.sum = sum;
}

int main(int argc, char** argv) {
    long long nterms = 1000000000000LL;
    int nthreads = 1;

    // Parse command line arguments
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];

        if (arg == "-terms" && i + 1 < argc) {
            nterms = std::stoll(argv[++i]);
        }

        if (arg == "-threads" && i + 1 < argc) {
            nthreads = std::stoi(argv[++i]);
        }
    }

    std::cout << "Terms: " << nterms << std::endl;
    std::cout << "Threads: " << nthreads << std::endl;

    std::vector<std::thread> threads;
    threads.reserve(nthreads);

    std::vector<dataa> data(nthreads);

    // Split work evenly across threads
    for (int i = 0; i < nthreads; i++) {
        data[i].a = 1 + (nterms * i) / nthreads;
        data[i].b = 1 + (nterms * (i + 1)) / nthreads;
        data[i].sum = 0.0;

        threads.emplace_back(harm, std::ref(data[i]));
    }

    // Wait for all threads
    for (std::thread& t : threads) {
        t.join();
    }

    // Combine results
    double total = 0.0;
    for (const dataa& d : data) {
        total += d.sum;
    }

    std::cout << "Total sum = " << total << std::endl;

    return 0;
}