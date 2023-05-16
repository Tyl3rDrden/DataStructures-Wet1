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
    class Statistics
    {
    private:
        int m_views;
        double m_rating; 

    public:
        Statistics(int views = 0);

        int getViews() const;
        void setViews(int views);

        double getRating() const;
        void setRating(double rating);
    };

private:
    int m_id;
    bool m_vipOnly;
    Genre m_genre;
    Statistics m_statistics;

public:
    Movie(int movieId, Genre genre, int views, bool vipOnly);

    int getId() const;

    bool getVipOnly() const;
    void setVipOnly(bool vipOnly);

    Genre getGenre() const;
    void setGenre(Genre genre);

    Statistics getStatistics() const;
    void setStatistics(const Statistics& stats);
};

	struct CompareMovieIDFunctor {
		bool operator()(const Movie& a, const Movie& b) {
			if (a.getId() == b.getId()) {
				throw IdAlreadyExists("Identical Id's");
			}
			return a.getId() < b.getId();
            //Return Right is bigger than left!
		}
	};
    struct CompareMovieStatisticsFunctor {
		bool operator()(const Movie& a, const Movie& b) {
			if (a.getId() == b.getId()) {
				throw std::invalid_argument("Identical Id's");
			}
            //Implement here the comparison based on statistics!
			return ;
            //Return Right is bigger than left!
		}
	};

#endif
