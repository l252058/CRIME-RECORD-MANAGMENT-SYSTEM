#ifndef VALIDITY_H
#define VALIDITY_H

// ─────────────────────────────────────────
//  CHAR UTILS CLASS
// ─────────────────────────────────────────

class CharUtils
{
public:

    static int length(const char* inputString)
    {
        int count = 0;
        while (inputString[count] != '\0')
        {
            count++;
        }
        return count;
    }

    static void copy(char* destinationBuffer, const char* sourceString)
    {
        int index = 0;
        while (sourceString[index] != '\0')
        {
            destinationBuffer[index] = sourceString[index];
            index++;
        }
        destinationBuffer[index] = '\0';
    }

    static void append(char* destinationBuffer, const char* sourceString)
    {
        int destinationEnd = length(destinationBuffer);
        int sourceIndex    = 0;

        while (sourceString[sourceIndex] != '\0')
        {
            destinationBuffer[destinationEnd] = sourceString[sourceIndex];
            destinationEnd++;
            sourceIndex++;
        }
        destinationBuffer[destinationEnd] = '\0';
    }

    static bool endsWith(const char* inputString, const char* suffix)
    {
        int stringLength = length(inputString);
        int suffixLength = length(suffix);

        if (stringLength < suffixLength)
        {
            return false;
        }

        int startIndex = stringLength - suffixLength;

        for (int index = 0; index < suffixLength; index++)
        {
            if (inputString[startIndex + index] != suffix[index])
            {
                return false;
            }
        }
        return true;
    }

    static bool isLetter(char inputChar)
    {
        return (inputChar >= 'a' && inputChar <= 'z')
        || (inputChar >= 'A' && inputChar <= 'Z');
    }

    static bool isDigit(char inputChar)
    {
        return inputChar >= '0' && inputChar <= '9';
    }

    static bool isUppercase(char inputChar)
    {
        return inputChar >= 'A' && inputChar <= 'Z';
    }

    static bool isAlphanumeric(char inputChar)
    {
        return isLetter(inputChar) || isDigit(inputChar);
    }

    static void intToChars(char* outputBuffer, int inputNumber)
    {
        if (inputNumber == 0)
        {
            outputBuffer[0] = '0';
            outputBuffer[1] = '\0';
            return;
        }

        char reverseBuffer[32];
        int  reverseIndex = 0;

        while (inputNumber > 0)
        {
            reverseBuffer[reverseIndex] = '0' + (inputNumber % 10);
            reverseIndex++;
            inputNumber /= 10;
        }

        int forwardIndex = 0;
        while (reverseIndex > 0)
        {
            outputBuffer[forwardIndex] = reverseBuffer[--reverseIndex];
            forwardIndex++;
        }
        outputBuffer[forwardIndex] = '\0';
    }
};


// ─────────────────────────────────────────
//  EMAIL VALIDATOR CLASS
// ─────────────────────────────────────────

class EmailValidator
{
private:

    char emailAddress[256];
    char validationMessage[256];
    bool isEmailValid;

    bool hasAtSymbol()
    {
        for (int index = 0; emailAddress[index] != '\0'; index++)
        {
            if (emailAddress[index] == '@')
            {
                return true;
            }
        }
        return false;
    }

    int findAtSymbolIndex()
    {
        for (int index = 0; emailAddress[index] != '\0'; index++)
        {
            if (emailAddress[index] == '@')
            {
                return index;
            }
        }
        return -1;
    }

    bool hasCharactersBeforeAt()
    {
        return findAtSymbolIndex() > 0;
    }

    bool domainHasDot()
    {
        int          atIndex    = findAtSymbolIndex();
        const char*  domainPart = emailAddress + atIndex + 1;

        for (int index = 0; domainPart[index] != '\0'; index++)
        {
            if (domainPart[index] == '.')
            {
                return true;
            }
        }
        return false;
    }

    bool hasValidEnding()
    {
        const char* validEndings[] = { ".com", ".net", ".org", ".edu", ".pk", nullptr };

        for (int index = 0; validEndings[index] != nullptr; index++)
        {
            if (CharUtils::endsWith(emailAddress, validEndings[index]))
            {
                return true;
            }
        }
        return false;
    }

    bool hasNoSpaces()
    {
        for (int index = 0; emailAddress[index] != '\0'; index++)
        {
            if (emailAddress[index] == ' ')
            {
                return false;
            }
        }
        return true;
    }

    bool localPartIsValid()
    {
        int atIndex = findAtSymbolIndex();

        for (int index = 0; index < atIndex; index++)
        {
            char currentChar = emailAddress[index];

            bool isAllowed = CharUtils::isAlphanumeric(currentChar)
                             || currentChar == '.'
                             || currentChar == '_'
                             || currentChar == '%'
                             || currentChar == '+'
                             || currentChar == '-';

            if (!isAllowed)
            {
                return false;
            }
        }
        return true;
    }

    bool domainPartIsValid()
    {
        int         atIndex    = findAtSymbolIndex();
        const char* domainPart = emailAddress + atIndex + 1;

        for (int index = 0; domainPart[index] != '\0'; index++)
        {
            char currentChar = domainPart[index];

            bool isAllowed = CharUtils::isAlphanumeric(currentChar)
                             || currentChar == '.'
                             || currentChar == '-';

            if (!isAllowed)
            {
                return false;
            }
        }
        return true;
    }

public:

    EmailValidator()
    {
        emailAddress[0]      = '\0';
        validationMessage[0] = '\0';
        isEmailValid         = false;
    }

    void setEmail(const char* inputEmail)
    {
        CharUtils::copy(emailAddress, inputEmail);
        isEmailValid         = false;
        validationMessage[0] = '\0';
    }

    bool validate()
    {
        if (emailAddress[0] == '\0')
        {
            CharUtils::copy(validationMessage, "Email cannot be empty.");
            isEmailValid = false;
            return false;
        }

        if (!hasAtSymbol())
        {
            CharUtils::copy(validationMessage, "Email must contain '@'.");
            isEmailValid = false;
            return false;
        }

        if (!hasCharactersBeforeAt())
        {
            CharUtils::copy(validationMessage, "Email must have characters before '@'.");
            isEmailValid = false;
            return false;
        }

        if (!domainHasDot())
        {
            CharUtils::copy(validationMessage, "Email domain must contain a dot (e.g. gmail.com).");
            isEmailValid = false;
            return false;
        }

        if (!hasValidEnding())
        {
            CharUtils::copy(validationMessage, "Email must end with .com / .net / .org / .edu / .pk");
            isEmailValid = false;
            return false;
        }

        if (!hasNoSpaces())
        {
            CharUtils::copy(validationMessage, "Email must not contain spaces.");
            isEmailValid = false;
            return false;
        }

        if (!localPartIsValid())
        {
            CharUtils::copy(validationMessage, "Email local part contains invalid characters.");
            isEmailValid = false;
            return false;
        }

        if (!domainPartIsValid())
        {
            CharUtils::copy(validationMessage, "Email domain contains invalid characters.");
            isEmailValid = false;
            return false;
        }

        CharUtils::copy(validationMessage, "Email is valid.");
        isEmailValid = true;
        return true;
    }

    bool        getIsValid() const { return isEmailValid;      }
    const char* getMessage() const { return validationMessage; }
};


// ─────────────────────────────────────────
//  PASSWORD VALIDATOR CLASS
// ─────────────────────────────────────────

class PasswordValidator
{
private:

    char passwordText[256];
    char validationMessage[512];
    char issuesCollected[512];
    bool isPasswordValid;
    int  strengthScore;

    void appendIssue(const char* issueMessage)
    {
        if (issuesCollected[0] != '\0')
        {
            CharUtils::append(issuesCollected, "\n");
        }
        CharUtils::append(issuesCollected, issueMessage);
    }

    bool meetsMinimumLength()
    {
        return CharUtils::length(passwordText) >= 8;
    }

    bool hasUppercaseLetter()
    {
        for (int index = 0; passwordText[index] != '\0'; index++)
        {
            if (CharUtils::isUppercase(passwordText[index]))
            {
                return true;
            }
        }
        return false;
    }

    bool hasDigit()
    {
        for (int index = 0; passwordText[index] != '\0'; index++)
        {
            if (CharUtils::isDigit(passwordText[index]))
            {
                return true;
            }
        }
        return false;
    }

    bool hasSpecialCharacter()
    {
        const char* allowedSpecials = "!@#$%^&*";

        for (int index = 0; passwordText[index] != '\0'; index++)
        {
            for (int specialIndex = 0; allowedSpecials[specialIndex] != '\0'; specialIndex++)
            {
                if (passwordText[index] == allowedSpecials[specialIndex])
                {
                    return true;
                }
            }
        }
        return false;
    }

    bool hasNoSpaces()
    {
        for (int index = 0; passwordText[index] != '\0'; index++)
        {
            if (passwordText[index] == ' ')
            {
                return false;
            }
        }
        return true;
    }

    bool hasNoPipeCharacter()
    {
        for (int index = 0; passwordText[index] != '\0'; index++)
        {
            if (passwordText[index] == '|')
            {
                return false;
            }
        }
        return true;
    }

    void clampStrengthScore()
    {
        if (strengthScore < 0)
        {
            strengthScore = 0;
        }
        if (strengthScore > 100)
        {
            strengthScore = 100;
        }
    }

public:

    PasswordValidator()
    {
        passwordText[0]      = '\0';
        validationMessage[0] = '\0';
        issuesCollected[0]   = '\0';
        isPasswordValid      = false;
        strengthScore        = 0;
    }

    void setPassword(const char* inputPassword)
    {
        CharUtils::copy(passwordText, inputPassword);
        isPasswordValid      = false;
        strengthScore        = 0;
        validationMessage[0] = '\0';
        issuesCollected[0]   = '\0';
    }

    bool validate()
    {
        strengthScore      = 0;
        issuesCollected[0] = '\0';

        if (!meetsMinimumLength())
        {
            char lengthMessage[64] = "At least 8 characters (Current: ";
            char numberBuffer[16];
            CharUtils::intToChars(numberBuffer, CharUtils::length(passwordText));
            CharUtils::append(lengthMessage, numberBuffer);
            CharUtils::append(lengthMessage, ")");
            appendIssue(lengthMessage);
        }
        else
        {
            strengthScore += 25;
        }

        if (!hasUppercaseLetter())
        {
            appendIssue("Must contain an UPPERCASE letter");
        }
        else
        {
            strengthScore += 25;
        }

        if (!hasDigit())
        {
            appendIssue("Must contain a digit (0-9)");
        }
        else
        {
            strengthScore += 25;
        }

        if (!hasSpecialCharacter())
        {
            appendIssue("Must contain a special character (!@#$%^&*)");
        }
        else
        {
            strengthScore += 25;
        }

        if (!hasNoSpaces())
        {
            appendIssue("Must not contain spaces");
            strengthScore -= 10;
        }

        if (!hasNoPipeCharacter())
        {
            appendIssue("Must not contain pipe character (|)");
            strengthScore -= 10;
        }

        clampStrengthScore();

        if (issuesCollected[0] != '\0')
        {
            CharUtils::copy(validationMessage, issuesCollected);
            isPasswordValid = false;
            return false;
        }

        CharUtils::copy(validationMessage, "Password is strong!");
        isPasswordValid = true;
        return true;
    }

    bool        getIsValid()       const { return isPasswordValid;   }
    const char* getMessage()       const { return validationMessage; }
    int         getStrengthScore() const { return strengthScore;     }
};


// ─────────────────────────────────────────
//  USERNAME VALIDATOR CLASS
// ─────────────────────────────────────────

class UsernameValidator
{
private:

    char usernameText[64];
    char validationMessage[256];
    bool isUsernameValid;

    bool meetsMinimumLength()
    {
        return CharUtils::length(usernameText) >= 3;
    }

    bool doesNotExceedMaximumLength()
    {
        return CharUtils::length(usernameText) <= 20;
    }

    bool containsOnlyAllowedCharacters()
    {
        for (int index = 0; usernameText[index] != '\0'; index++)
        {
            char currentChar = usernameText[index];

            bool isAllowed = CharUtils::isAlphanumeric(currentChar)
                             || currentChar == '_';

            if (!isAllowed)
            {
                return false;
            }
        }
        return true;
    }

public:

    UsernameValidator()
    {
        usernameText[0]      = '\0';
        validationMessage[0] = '\0';
        isUsernameValid      = false;
    }

    void setUsername(const char* inputUsername)
    {
        CharUtils::copy(usernameText, inputUsername);
        isUsernameValid      = false;
        validationMessage[0] = '\0';
    }

    bool validate()
    {
        if (usernameText[0] == '\0')
        {
            CharUtils::copy(validationMessage, "Username cannot be empty.");
            isUsernameValid = false;
            return false;
        }

        if (!meetsMinimumLength())
        {
            CharUtils::copy(validationMessage, "Username must be at least 3 characters.");
            isUsernameValid = false;
            return false;
        }

        if (!doesNotExceedMaximumLength())
        {
            CharUtils::copy(validationMessage, "Username must not exceed 20 characters.");
            isUsernameValid = false;
            return false;
        }

        if (!containsOnlyAllowedCharacters())
        {
            CharUtils::copy(validationMessage, "Username can only contain letters, digits, and underscores.");
            isUsernameValid = false;
            return false;
        }

        CharUtils::copy(validationMessage, "Username is valid.");
        isUsernameValid = true;
        return true;
    }

    bool        getIsValid() const { return isUsernameValid;   }
    const char* getMessage() const { return validationMessage; }
};

#endif // VALIDITY_H