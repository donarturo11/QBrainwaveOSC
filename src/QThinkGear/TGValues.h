#ifndef TGVALUES_H
#define TGVALUES_H
struct tg_value {
    std::string key;
    std::string name;
};
const tg_value eegnames[] = {
        {"eegdelta" , "Delta"},
        {"eegtheta", "Theta"},
        {"eeglowalpha","Low alpha"},
        {"eeghighalpha", "High alpha"},
        {"eeglowbeta", "Low beta"},
        {"eeghighbeta", "High beta"},
        {"eeglowgamma", "Low gamma"},
        {"eeghighgamma", "High gamma"}
    };
/*
const valuename valuenames[] = {
        {"eegdelta" , "Delta"},
        {"eegtheta", "Theta"},
        {"eeglowalpha","Low alpha"},
        {"eeghighalpha", "High alpha"},
        {"eeglowbeta", "Low beta"},
        {"eeghighbeta", "High beta"},
        {"eeglowgamma", "Low gamma"},
        {"eeghighgamma", "High gamma"}
    };
*/
#endif // TGVALUES_H
