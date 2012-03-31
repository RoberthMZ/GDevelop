/** \file
 *  Game Develop
 *  2008-2012 Florian Rival (Florian.Rival@gmail.com)
 */
#if defined(GD_IDE_ONLY)

#ifndef GDEXPRESSIONPARSER_H
#define GDEXPRESSIONPARSER_H

#include <string>
#include <vector>
class GDExpression;
class ParserCallbacks;
class Game;
class Scene;
class ParameterMetadata;
class ExpressionInstruction;
class StrExpressionInstruction;
class ExpressionMetadata;
class StrExpressionMetadata;

/** \brief Internal class. Parse a plainExpression by calling functors at each token
 *
 * Parse the expression, and call functors when a token is reached
 * ( like a function call )
 */
class GD_API GDExpressionParser
{
    public:
        GDExpressionParser(const std::string & expressionPlainString_);
        virtual ~GDExpressionParser() {};

        /**
         * Parse the expression, calling each functor when necessary
         * \return True if expression was correctly parsed.
         */
        bool ParseMathExpression(const Game & game, const Scene & scene, ParserCallbacks & callbacks);

        /**
         * Parse the expression, calling each functor when necessary
         * \return True if expression was correctly parsed.
         */
        bool ParseTextExpression(const Game & game, const Scene & scene, ParserCallbacks & callbacks);

        #if defined(GD_IDE_ONLY)
        std::string firstErrorStr;
        size_t firstErrorPos;
        #endif

    private:

        /**
         * Tool function to add a parameter
         */
        bool AddParameterToList(const Game & game, const Scene & scene, ParserCallbacks &, std::vector < GDExpression > & parameters, std::string parameterStr, std::vector < ParameterMetadata > parametersInfos, const size_t positionInExpression);

        /**
         * Tool function to prepare a parameter
         */
        bool PrepareParameter(const Game & game, const Scene & scene, ParserCallbacks &, GDExpression & parameter, const ParameterMetadata & parametersInfo, const size_t positionInExpression);

        /**
         * Return the minimal number of parameters which can be used when calling an expression ( i.e. ParametersCount-OptionalParameters-CodeOnlyParameters )
         */
        size_t GetMinimalParametersNumber(const std::vector < ParameterMetadata > & parametersInfos);

        /**
         * Return the maximal number of parameters which can be used when calling an expression ( i.e. ParametersCount-CodeOnlyParameters )
         */
        size_t GetMaximalParametersNumber(const std::vector < ParameterMetadata > & parametersInfos);

        bool ValidSyntax(const std::string & str);

        std::string expressionPlainString;
        static std::string parserSeparators;
};

/** \brief Callbacks called by parser during parsing
 *
 * Parser will call the appropriate functions during parsing, allowing to do special works.
 */
class ParserCallbacks
{
    public:

    ParserCallbacks() {};
    virtual ~ParserCallbacks() {};

    virtual void OnConstantToken(std::string text) = 0;
    virtual void OnNumber(std::string text) = 0;
    virtual void OnOperator(std::string text) = 0;

    virtual void OnStaticFunction(std::string functionName, const std::vector<GDExpression> & parameters, const ExpressionMetadata & expressionInfo) = 0;
    virtual void OnStaticFunction(std::string functionName, const std::vector<GDExpression> & parameters, const StrExpressionMetadata & ExpressionMetadata) = 0;

    virtual void OnObjectFunction(std::string functionName, const std::vector<GDExpression> & parameters, const ExpressionMetadata & expressionInfo) = 0;
    virtual void OnObjectFunction(std::string functionName, const std::vector<GDExpression> & parameters, const StrExpressionMetadata & ExpressionMetadata) = 0;

    virtual void OnObjectAutomatismFunction(std::string functionName, const std::vector<GDExpression> & parameters, const ExpressionMetadata & expressionInfo) = 0;
    virtual void OnObjectAutomatismFunction(std::string functionName, const std::vector<GDExpression> & parameters, const StrExpressionMetadata & ExpressionMetadata) = 0;

    virtual bool OnSubMathExpression(const Game & game, const Scene & scene, GDExpression & expression) = 0;
    virtual bool OnSubTextExpression(const Game & game, const Scene & scene, GDExpression & expression) = 0;

    #if defined(GD_IDE_ONLY)
    std::string firstErrorStr;
    size_t firstErrorPos;
    #endif
};

#endif // GDEXPRESSIONPARSER_H

#endif
