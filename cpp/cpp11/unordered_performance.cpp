#include <unordered_set>
#include <iostream>
#include <random>

int main() {
    size_t experimentRange = 1000000000;
    size_t totalElements = 1000000;
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1, experimentRange);

    std::unordered_set<size_t> input;
    
    while (totalElements--) {
        while (!input.insert(dist(rng)).second) {}
    }

    std::unordered_set<size_t> bucketIds;
    for (size_t i : input) {
        bucketIds.emplace(input.bucket(i));
    }

    size_t sum = 0;
    size_t maxBucketSize = 0;
    for (size_t i : bucketIds) {
        size_t bucketSize = input.bucket_size(i);
        //std::cout << "bucket size " << bucketSize << std::endl;
        sum += bucketSize;
        maxBucketSize = std::max(maxBucketSize, bucketSize);
    }

    std::cout << "sum " << sum << std::endl;
    std::cout << "size " << input.size() << std::endl;
    std::cout << "max " << maxBucketSize << std::endl;

    std::vector<size_t> countForEachSize(maxBucketSize + 2, 0);

    for (size_t i : bucketIds) {
        ++countForEachSize[input.bucket_size(i)];
    }
    
    size_t newSum = 0;
    for (size_t i = 1; i < countForEachSize.size(); ++i) {
        std::cout << i << "-> " << countForEachSize[i] << std::endl;
        newSum += i * countForEachSize[i];
    }

    std::cout << "New sum " << newSum << std::endl;

    double percentageSum = 0;
    for (size_t i = 1; i < countForEachSize.size(); ++i) {
        double percentage = (i * countForEachSize[i] / (double)sum) * 100;
        percentageSum += percentage;
        std::cout << i << "-> " << percentage << "%" << std::endl;
    }

    std::cout << "Percentage sum " << percentageSum << std::endl;

    return 0;
}
