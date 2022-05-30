
enum class menuChoice
{
    quit,
    help,
    insert,
    extract,
    save,
    print,

    wrong
};

void printMenu();
menuChoice hashTheChoice(std::string choice);

void printMenu() 
{
    std::cout << R"(
**********                                              **********
syntax: [Function]

[Function]:
    [-q] or [--quit]                        to quit the application
    [-h] or [--help]                        to print this menu
    [-p] or [--print]                       to print all jobs
    [-i] or [--insert] + [a Job]            to add a job
    [-e] or [--extraction] + [a Job]        to take out a job
    [-s] or [--save]                        to save
    
)";
}

menuChoice hashTheChoice(std::string choice)
{
    if (choice == "-q" || choice == "--quit")
        return menuChoice::quit;
    if (choice == "-h" || choice == "--help")
        return menuChoice::help;
    if (choice == "-p" || choice == "--print")
        return menuChoice::print;
    if (choice == "-i" || choice == "--insert")
        return menuChoice::insert;
    if (choice == "-e" || choice == "--extract")
        return menuChoice::extract;
    if (choice == "-s" || choice == "--save")
        return menuChoice::save;

    return menuChoice::wrong;
}