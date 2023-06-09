#ifndef _MOVIE_H
#define _MOVIE_H
#include <exception>
#include <stdexcept>
#include "wet1util.h"
#include "Wet1Exceptions.h"
//Need to separate these into differint files!

// Here I am defining all the classes and structs needed for the code to work


class Movie
{
public:
    class Statistics
    {
        friend Movie;
    private:
        int m_id;
        int m_views;
        double m_rating;
        int m_sumRating;
        int m_numeberOfRatings;

    public:
        Statistics(int views =0, int id=0)
                : m_views(views), m_rating(0.0), m_id(id), m_sumRating(0), m_numeberOfRatings(0) {}
        //Could be an issue here With The default value Its only here to fill and entirre Array
        int getViews() const;
        void setViews(int views);
        int getId() const;
        double getRating() const;
        void addRating(int rating);
        bool operator!=(const Statistics& other) const; // For my AVL TREE
        //Statistics are differint if their if is differint!
    };

private:
    int m_id;
    bool m_vipOnly;
    Genre m_genre;
    Statistics m_statistics;

public:
    Movie(int movieId, Genre genre, int views, bool vipOnly);
    void IncrementViews(int amount);
    const int& getId() const;
    void addRating(int rating);
    bool getVipOnly() const;
    void setVipOnly(bool vipOnly);

    Genre getGenre() const;
    void setGenre(Genre genre);
    const int* getMovieIdPtr()
    {
        return &m_id;
    }
    const Statistics& getStatistics() const;
    const Statistics* getStatisticsPtr() const;
    void setStatistics(const Statistics& stats);
};

struct CompareMovieIDFunctor {
    bool operator()(const int& a, const int& b) {
        if (a == b) {
            throw IdAlreadyExists("Identical Id's");
        }
        return a < b;
        //Return Right is bigger than left!
    }
};
struct CompareMovieStatisticsFunctor {
    bool operator()(const Movie::Statistics& a, const Movie::Statistics& b) {
        if (a.getId() == b.getId()) {
            throw std::invalid_argument("Identical Id's");
        }
        //Implement here the comparison based on statistics!
        if(a.getRating() != b.getRating())
        {//Double comparison is a tricky topic .. ask on piazza
            return a.getRating() < b.getRating();
        }
        else if(a.getViews() != b.getViews())
        {
            return a.getViews() < b.getViews();
        }
        else
        {
            return a.getId() > b.getId();
        }
        //Return Right is bigger than left!
        //It's never going to get here;
        throw std::invalid_argument("Reached Bad place!");
        return false;
    }
};

#endif
