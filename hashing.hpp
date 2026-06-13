#include "pre_compiled.hpp"

class Database
{
    private:
        std::string* m_username;
        unsigned long long* m_password;
        std::string* m_email;
        int m_count;
        int m_cap;

        void grow();

        unsigned long long hash_password(const std::string& password) const;

    public:
        Database(int initial_cap = 10);
        ~Database();

        void add_user(const std::string& username, const std::string& password, const std::string& email);
        bool verify_user(const std::string& username, const std::string& password);
        bool user_exists(const std::string& username);
        int get_count() const;
        void save_to_file(const char* path) const;
        void load_from_file(const char* path);
};