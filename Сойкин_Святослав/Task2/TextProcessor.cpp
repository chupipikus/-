#include "pch.h"
#include "TextProcessor.h"
#include <locale>
#include <cctype>

// Построить частотный словарь слов из файла
map<string, double> TextProcessor::makeWordsFrequencyDict(const string& fileName) {
    map<string, double> freqDict;

    fstream fs(fileName, ios::in);
    if (!fs.is_open()) {
        throw exception(("TextProcessor: Не удалось открыть файл " + fileName).c_str());
    }
    fs.imbue(locale(".1251"));

    int wordsCounter = 0;
    string line;
    while (getline(fs, line)) {
        if (line.empty()) continue;

        vector<string> words = splitBySpace(line);
        for (const auto& word : words) {
            freqDict[word] += 1.0;
        }
        wordsCounter += static_cast<int>(words.size());
    }
    fs.close();
    if (wordsCounter > 0) {
        for (auto& item : freqDict) {
            item.second /= wordsCounter;
        }
    }
    return freqDict;
}

map<string, double> TextProcessor::makeLettersFrequencyDict(const string& fileName) {
    map<string, double> freqDict;

    fstream fs(fileName, ios::in);
    if (!fs.is_open()) {
        throw exception(("TextProcessor: Не удалось открыть файл " + fileName).c_str());
    }
    fs.imbue(locale(".1251"));

    string text;
    string line;
    while (getline(fs, line)) {
        if (!text.empty()) text += ' ';
        text += line;
    }
    fs.close();

    int lettersCounter = 0;
    for (char c : text) {
        if (isalpha(static_cast<unsigned char>(c))) {
            char lowerC = tolower(static_cast<unsigned char>(c));
            freqDict[string(1, lowerC)] += 1;
            lettersCounter++;
        }
    }

    if (lettersCounter > 0) {
        for (auto& item : freqDict) {
            item.second /= lettersCounter;
        }
    }
    return freqDict;
}

// splitBySpace
vector<string> TextProcessor::splitBySpace(const string& line) {
    vector<string> words;
    stringstream ss(line);
    string word;
    while (ss >> word) {
        if (!word.empty()) words.emplace_back(word);
    }
    return words;
}