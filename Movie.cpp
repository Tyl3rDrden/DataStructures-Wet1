#include "Movie.h"

Movie::Statistics::Statistics(int views, int id)
    : m_views(views), m_rating(0.0), m_id(id), m_sumRating(0), m_numeberOfRatings(0) {}

int Movie::Statistics::getViews() const
{
    return m_views;
}

void Movie::Statistics::setViews(int views)
{
    m_views = views;
}

double Movie::Statistics::getRating() const
{
    return m_rating;
}

void Movie::Statistics::addRating(int rating)
{
    if(rating < 0 || rating > 100)
    {
        throw std::invalid_argument("Bad Input Rating");
    }
    m_sumRating += rating;
    m_numeberOfRatings++;
    m_rating = m_sumRating / m_numeberOfRatings;

}
int Movie::Statistics::getId() const
{
    return m_id;
}
bool Movie::Statistics::operator!=(const Statistics& other) const
{
    return m_id != other.m_id;

}
Movie::Movie(int movieId, Genre genre, int views, bool vipOnly)
    : m_id(movieId), m_vipOnly(vipOnly), m_genre(genre), m_statistics(views, movieId) {}

const int& Movie::getId() const
{
    return m_id;
}

bool Movie::getVipOnly() const
{
    return m_vipOnly;
}

void Movie::setVipOnly(bool vipOnly)
{
    m_vipOnly = vipOnly;
}

Genre Movie::getGenre() const
{
    return m_genre;
}

void Movie::setGenre(Genre genre)
{
    m_genre = genre;
}

const Movie::Statistics& Movie::getStatistics() const
{
    return m_statistics;
}
const Movie::Statistics* Movie::getStatisticsPtr() const
{
    return &m_statistics;
}
void Movie::setStatistics(const Statistics& stats)
{
    m_statistics = stats;
}

void Movie::IncrementViews(int amount)
{
    m_statistics.m_views+= amount;
}


void Movie::addRating(int rating)
{
    m_statistics.addRating(rating);

}