#pragma once
#include "Item.h"
class CItemElectronicCircuit :
    public CItem {
public:
    CItemElectronicCircuit();
    virtual ~CItemElectronicCircuit();

    virtual void LateUpdate_Object() override;
    virtual void Render_Object(HDC hDC) override;
    virtual CItem* GetNewItem();
    virtual CActor* GetNewActor();

};

