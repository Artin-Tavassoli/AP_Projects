#include <iostream>
#include <vector>
#include <string.h>
using namespace std;
namespace error_messages
{
    const string MINIMUM_UNIT = "Minimum Units Validation Failed!";
    const string MINIMUM_UNIT = "Maximum Units Validation Failed!";
    const string COURSE_ALREADY_TAKEN = "Course Already Taken!";
    const string COURSE_NOT_OFFERED = "Course Not Offered!";
    const string PREREQUISITES_NOT_MET = "Prerequisites Not Met!";
}
const char SEPERATOR = ',';
const string SUCCUSSFUL_MESSAGE = "OK!";


bool check_num_units(vector<string> name_of_wanted_courses, vector<string> available_courses_name, vector<int> num_units_available, double GPA)
{
    int sum = 0;
    for (int i = 0; i < name_of_wanted_courses.size(); i++)
    {
        for (int j = 0; j < available_courses_name.size(); j++)
        {
            if (name_of_wanted_courses[i] == available_courses_name[j])
            {
                sum += num_units_available[j];
            }
        }
    }
    if (sum < 12)
    {
        cout << error_messages::MINIMUM_UNIT;
        return false;
    }
    if (GPA >= 17 && sum > 24)
    {
        cout << error_messages::MINIMUM_UNIT;
        return false;
    }
    if (GPA >= 12 && GPA < 17 && sum > 20)
    {
        cout << error_messages::MINIMUM_UNIT;
        return false;
    }
    if (GPA < 12 && sum > 14)
    {
        cout << error_messages::MINIMUM_UNIT;
        return false;
    }
    return true;
}

int course_repetitive(vector<string> name_of_wanted_courses, vector<string> taken_courses_name, vector<double> grade)
{
    for (int i = 0; i < name_of_wanted_courses.size(); i++)
    {
        for (int j = 0; j < taken_courses_name.size(); j++)
        {
            if (name_of_wanted_courses[i] == taken_courses_name[j] && grade[j] >= 10)
            {
                cout << error_messages::COURSE_ALREADY_TAKEN;
                return 1;
            }
        }
    }
    return 0;
}

int course_existance(vector<string> name_of_wanted_courses, vector<string> available_courses_name)
{
    bool course_exist = false;
    for (int i = 0; i < name_of_wanted_courses.size(); i++)
    {
        for (int j = 0; j < available_courses_name.size(); j++)
        {
            if (name_of_wanted_courses[i] == available_courses_name[j])
                course_exist = true;
        }
        if (!course_exist)
        {
            cout << error_messages::COURSE_NOT_OFFERED;
            return 1;
        }
        course_exist = false;
    }
    return 0;
}

int check_prerequisites(vector<string> name_of_wanted_courses, vector<string> available_courses_name, vector<string> prerequisites_string, vector<string> taken_courses_name, vector<double> grade)
{
    for (int i = 0; i < name_of_wanted_courses.size(); i++)
    {
        for (int j = 0; j < available_courses_name.size(); j++)
        {
            if (name_of_wanted_courses[i] == available_courses_name[j])
            {
                string tempp;
                for (int k = 0; k <= prerequisites_string[j].size(); k++)
                {
                    bool has_prq = false;
                    if (prerequisites_string[j][k] == SEPERATOR || k == prerequisites_string[j].size())
                    {
                        for (int g = 0; g < taken_courses_name.size(); g++)
                        {
                            if (tempp == taken_courses_name[g] && grade[g] >= 10)
                            {
                                has_prq = true;
                            }
                        }
                        if (has_prq == false)
                        {
                            cout << error_messages::PREREQUISITES_NOT_MET;
                            return 1;
                        }
                        tempp = "";
                    }
                    else
                    {
                        tempp += prerequisites_string[j][k];
                    }
                }
            }
        }
    }
    return 0;
}

void get_input(vector<string> &available_courses_name,
               vector<int> &num_units_available,
               vector<string> &prerequisites_string,
               vector<string> &taken_courses_name,
               vector<double> &grade,
               double &GPA,
               vector<string> &name_of_wanted_courses)
{
    int number_of_available_courses;
    cin >> number_of_available_courses;
    string temp;
    int temp2;
    string temp3;
    for (int i = 0; i < number_of_available_courses; i++)
    {
        cin >> temp;
        available_courses_name.push_back(temp);
        cin >> temp2;
        num_units_available.push_back(temp2);
        cin >> temp3;
        prerequisites_string.push_back(temp3);
    }
    int number_of_taken_courses;
    cin >> number_of_taken_courses;
    vector<int> num_units_taken;
    double temp4;
    int sum_units_taken = 0;
    for (int i = 0; i < number_of_taken_courses; i++)
    {
        cin >> temp;
        taken_courses_name.push_back(temp);
        cin >> temp2;
        num_units_taken.push_back(temp2);
        cin >> temp4;
        grade.push_back(temp4);
        GPA += temp2 * temp4;
        sum_units_taken += temp2;
    }
    GPA = GPA / (sum_units_taken);
    int number_of_wanted_courses;
    cin >> number_of_wanted_courses;
    for (int i = 0; i < number_of_wanted_courses; i++)
    {
        cin >> temp;
        name_of_wanted_courses.push_back(temp);
    }
}

void run_program()
{
    vector<string> available_courses_name;
    vector<int> num_units_available;
    vector<string> prerequisites_string;
    vector<string> taken_courses_name;
    vector<double> grade;
    double GPA = 0;
    vector<string> name_of_wanted_courses;
    get_input(available_courses_name, num_units_available, prerequisites_string, taken_courses_name, grade, GPA, name_of_wanted_courses);
    bool error_occurred = false;
    error_occurred = course_existance(name_of_wanted_courses, available_courses_name);
    error_occurred = course_repetitive(name_of_wanted_courses, taken_courses_name, grade);
    error_occurred = check_num_units(name_of_wanted_courses, available_courses_name, num_units_available, GPA);
    error_occurred = check_prerequisites(name_of_wanted_courses, available_courses_name, prerequisites_string, taken_courses_name, grade);
    if (!error_occurred)
    {
        cout << SUCCUSSFUL_MESSAGE;
    }
}

int main()
{
    run_program();
    return 0;
}