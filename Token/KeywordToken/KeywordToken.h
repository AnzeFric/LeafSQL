//
// Created by anzef on 21. 12. 2025.
//

#ifndef LEAFSQL_KEYWORDTOKEN_H
#define LEAFSQL_KEYWORDTOKEN_H

#include <string>
#include "../Token.h"
#include "../Types/KeywordType.h"

class KeywordToken : public Token {
private:
    KeywordType keywordType;
public:
    KeywordToken(TokenType type, const std::string &value, const std::string& keywordStr);
    KeywordToken(const Token& token, const std::string& keywordStr);
    [[nodiscard]] KeywordType getKeywordType() const;
};

#endif //LEAFSQL_KEYWORDTOKEN_H
