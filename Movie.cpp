#include "Movie.h"

Movie::Statistics::Statistics(int views, int id)
    : m_views(views), m_rating(0.0), m_id(id) {}

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

void Movie::Statistics::setRating(double rating)
{
    m_rating = rating;
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

int Movie::getId() const
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
