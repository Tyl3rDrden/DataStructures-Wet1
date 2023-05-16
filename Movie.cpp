#include "Movie.h"

Movie::Statistics::Statistics(int views)
    : m_views(views), m_rating(0.0) {}

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

Movie::Movie(int movieId, Genre genre, int views, bool vipOnly)
    : m_id(movieId), m_vipOnly(vipOnly), m_genre(genre), m_statistics(views) {}

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

Movie::Statistics Movie::getStatistics() const
{
    return m_statistics;
}

void Movie::setStatistics(const Statistics& stats)
{
    m_statistics = stats;
}