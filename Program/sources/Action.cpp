#include "../headers/Action.hpp"

NAction::Subject getDoer(const action& a){
return (NAction::Subject) (a>>7);
}

NAction::Subject getTarget(const action& a){
return (NAction::Subject) ( (a<<1)>>7);
}

NAction::Action getAction(const action& a){
return (NAction::Action) ( (a<<2)>>2);
}
