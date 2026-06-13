#include "../header/hashing.hpp"

unsigned long long Database::hash_password(const std::string& password) const
{
    unsigned long long hash = 1;
    for (int i = 0; i < password.size(); i++) 
    {
        hash = hash * 31 + password[i];
    }
    return hash;
}

void Database::grow()
{
    m_cap *= 2;

    std::string* new_username = new std::string[m_cap];
    unsigned long long* new_password = new unsigned long long[m_cap];
    std::string* new_email = new std::string[m_cap];

    for (int i = 0; i < m_count; i++) {
        new_username[i] = m_username[i];
        new_password[i] = m_password[i];
        new_email[i] = m_email[i];
    }

    delete[] m_username;
    delete[] m_password;
    delete[] m_email;

    m_username = new_username;
    m_password = new_password;
    m_email = new_email;
}

Database::Database(int initial_cap) : m_count(0), m_cap(initial_cap)
{
    m_username = new std::string[m_cap];
    m_password = new unsigned long long[m_cap];
    m_email = new std::string[m_cap];
}

Database::~Database()
{
    delete[] m_username;
    delete[] m_password;
    delete[] m_email;
}

void Database::add_user(const std::string& username, const std::string& password, const std::string& email)
{
    if (user_exists(username))
    {
        std::cerr << "Database: username '" << username << "' already exists.\n";
        return;
    }
    if (m_count == m_cap)
        grow();

    m_username[m_count] = username;
    m_password[m_count] = hash_password(password);
    m_email[m_count] = email;
    ++m_count;
}

bool Database::verify_user(const std::string& username, const std::string& password)
{
    unsigned long long hashed = hash_password(password);
    for (int i = 0; i < m_count; ++i)
    {
        if (m_username[i] == username && m_password[i] == hashed)
            return true;
    }
    return false;
}

bool Database::user_exists(const std::string& username)
{
    for (int i = 0; i < m_count; i++) 
    {
        if (m_username[i] == username) 
        {
            return true;
        }
    }
    return false;
}

int Database::get_count() const
{
    return m_count;
}

void Database::save_to_file(const char* path) const
{
    std::ofstream out(path);
    if (!out.is_open()) { std::cerr << "Database: cannot open " << path << "\n"; return; }

    for (int i = 0; i < m_count; ++i)
        out << m_username[i] << ' ' << m_password[i] << ' ' << m_email[i] << '\n';
}

void Database::load_from_file(const char* path)
{
    std::ifstream in(path);
    if (!in.is_open()) return;  

    std::string        uname, email;
    unsigned long long hashed;

    while (in >> uname >> hashed >> email)
    {
        if (m_count == m_cap) grow();
        m_username[m_count] = uname;
        m_password[m_count] = hashed;
        m_email[m_count]    = email;
        ++m_count;
    }
}