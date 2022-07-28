//find the average movie ratings
for (auto p : movieRatings) {
    // Key is an integer
    int key = p.first;
    
    // Value is a list of integers
    std::list<double> ratings = p.second;

    double sum;
    int count = 0;
    for (auto r = ratings.begin();
        r != ratings.end(); r++) {
        // Dereferencing value pointed by iterator
        sum += *r;
        count++;
    }
    movieRatingAvg[key] = sum/count;
}

//remove the movies that the user has watched


//get the top 5 movies
std::vector<std::pair<int, int>> top_five(5);
std::partial_sort_copy(movieRatingAvg.begin(),
    movieRatingAvg.end(),
    top_five.begin(),
    top_five.end(),
    [](std::pair<const int, int> const& l,
        std::pair<const int, int> const& r)
    {
        return l.second > r.second;
    }
);