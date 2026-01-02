//
// Created by anzef on 21. 12. 2025.
//

#include "KeywordToken.h"
#include <unordered_map>
#include <stdexcept>

KeywordType stringToKeywordType(const std::string& value) {
    static const std::unordered_map<std::string, KeywordType> keywordMap = {
        {"SELECT", KeywordType::SELECT},
        {"INSERT", KeywordType::INSERT},
        {"DELETE", KeywordType::DELETE},
        {"UPDATE", KeywordType::UPDATE},
        {"CREATE", KeywordType::CREATE}
    };

    if (const auto it = keywordMap.find(value); it != keywordMap.end()) {
        return it->second;
    }

    throw std::runtime_error("Unknown keyword: " + value);
}

KeywordToken::KeywordToken(const TokenType type, const std::string &value, const std::string& keywordStr): Token(type, value) {
    this->keywordType = stringToKeywordType(keywordStr);
};

KeywordToken::KeywordToken(const Token& token, const std::string& keywordStr) : Token(token) {
    this->keywordType = stringToKeywordType(keywordStr);
};

KeywordType KeywordToken::getKeywordType() const {
    return this->keywordType;
};
