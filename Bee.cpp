#include "Bee.hpp"
#include "Application.hpp"
#include "Utility/Utility.hpp"



Bee::Bee(const Vec2d& position, const double& arg_diam, Hive& Home, const double& energy, const double& ScalSpeed)
    :Collider(position, arg_diam*2),
      Home(Home),
      speed(Vec2d::fromRandomAngle()*ScalSpeed),
      energy(energy) {}                                    // constructeur
j::Value const& getConfig(){
    return getValueConfig()["simulation"]["bee"]["scout"];
}

void Bee::drawOn(sf::RenderTarget& target) const {                           // dessine une abeille
    auto const& sprite = getAppTexture(getValueConfig()["simulation"]["scout"]["textures"].toString());
    double α=Vec2d::angle(speed);

    if (α >= PI / 2 or α <= -PI/2){
        sprite.scale(1, -1);

        do{
        sprite.rotate(α /DEG_TO_RAD);
        }
    }else{
        sprite.rotate(α /DEG_TO_RAD);
    }
    auto BeeSprite = buildSprite(center, radius*2, sprite);
    target.draw(BeeSprite);
}
