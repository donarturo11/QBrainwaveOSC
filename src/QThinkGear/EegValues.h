#ifndef EEGVALUES_H
#define EEGVALUES_H
#include <string>
#include <list>
#include "TGValues.h"

class EegValue {
public: 
    EegValue(std::string key, std::string name, int value = 0)
    {
        _key = key;
        _name = name;
        _value = value;
    }
    unsigned int operator=(EegValue&) const { return value(); }
    void operator=(unsigned int val) { setValue(val); }
    std::string key() const { return _key; }
    std::string name() const { return _name; }
    unsigned int value() const { return _value; }
    void setValue(int v) { _value = v; }
private:    
    std::string _key;
    std::string _name;
    unsigned int _value;
}; 

const EegValue eegValueNull("", "", 0);
    
class EegValues {
public:
    EegValues()
    {
        for (int i=0; i < 8; i++) {
            auto eeg = eegnames[i];
            _values.emplace_back(EegValue(eeg.key, eeg.name, 0));
        }
    }
    EegValues(std::vector<uint32_t> vec)
    {
        _sum = 0;
        for (int i=0; i < 8; i++) {
            auto eeg = eegnames[i];
            _values.emplace_back(EegValue(eeg.key, eeg.name, vec[i]));
            _sum += vec[i];
        }
    }
    
    EegValue operator[](std::string key){ return getValue(key); }
    EegValue getValue(std::string key)
    {
        for (auto i : _values) {
            if (i.key() == key)
                return i;
        }
        return eegValueNull;
    }
    
    EegValue operator[](int idx) { return getValueAt(idx); }
    EegValue getValueAt(int idx) { return (idx < _values.size()) ? _values[idx] : eegValueNull; }
    unsigned int sum() { return _sum; }
    void setValue(std::string key, int value)
    {
        for (auto i : _values) {
            if (i.key() == key) {
                _sum -= i.value();
                i.setValue(value);
                _sum += value;
            }
        }
    }
    void setValueAt(int idx, int value)
    { 
        if (idx >= _values.size()) return;
        _values[idx].setValue(value);
    }
    std::vector<EegValue> getAllValues() const { return _values; }
    
    
private:
    std::vector<EegValue> _values;
    unsigned int _sum;
};


#endif //  EEGVALUES_H
