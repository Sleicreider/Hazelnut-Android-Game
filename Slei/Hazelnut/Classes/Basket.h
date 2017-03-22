//
//  Basket.hpp
//  Hazelnut
//
//  Created by Dominik Reisner on 14.06.16.
//
//

#ifndef Basket_h
#define Basket_h

#include "FGeneral.h"
#include "FSprite.h"

class Basket : public FSprite
{
public:
    Basket();
    virtual ~Basket();
    
    static Basket* create(const std::string& filename, const std::string& fragment_shader);
    
    CREATE_FUNC(Basket);
    
private:
    void InitShader(const std::string& fragment_shader);
    
};

#endif /* Basket_h */
