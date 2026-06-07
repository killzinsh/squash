#include "advert_entity.h"

#include "entity_manager.h"

void InitAdverts(Advert* ads[], int adCnt)
{
    for (int i = 0; i < adCnt; i++)
        ads[i] = NULL;
}

bool SpawnAdvert(Advert* ads[], int adCnt, Rectangle playArea)
{   
    if (adCnt >= MAX_ADVERT_CNT) return false;

    static int horBannerCnt = 0;
    static int vertBannerCnt = 0;
    static int smallRectCnt = 0;
    static int bigRectCnt = 0;

    int seed = GetRandomValue(0, AD_RANGE_MAX);
    if (seed <= AD_HOR_BANNER_RATE && horBannerCnt <= MAX_HOR_BANNER_CNT)
    {
        ads[adCnt] = CreateAdvert(ENTITY_AD_HOR_BANNER, AD_HOR_BANNER_AREA(playArea.x, playArea.y, playArea.width, playArea.height));
    } 
    else if (seed <= AD_VERT_LEFT_BANNER_RATE && vertBannerCnt <= MAX_VERT_BANNER_CNT)
    {
        //ads[adCnt] = CreateAdvert(ENTITY_AD_VERT_BANNER, );
    }
    else if (seed <= AD_VERT_RIGHT_BANNER_RATE && vertBannerCnt <= MAX_VERT_BANNER_CNT)
    {
        //ads[adCnt] = CreateAdvert(ENTITY_AD_VERT_BANNER, );
    }
    else if (seed <= AD_SMALL_RECT_RATE && smallRectCnt <= MAX_SMALL_RECT_CNT)
    {
        //ads[adCnt] = CreateAdvert(ENTITY_AD_SMALL_RECT, );
    }
    else if (bigRectCnt <= MAX_BIG_RECT_CNT)
    {
        //ads[adCnt] = CreateAdvert(ENTITY_AD_BIG_RECT, );
    }
    
    printf("pointer to ad -> %p\n", ads[adCnt]);
    if (ads[adCnt] == NULL)  return false;
    else return true;
}

Advert* CreateAdvert(enum EntityId id, Rectangle adArea)
{
    Advert* ad = (Advert*)malloc(1 * sizeof(Advert));
    ad->obj.id = id;
    ad->adImage.texture = GetEntityTextures(id);
    ad->adImage.active = GetRandomValue(0, GetEntityTextureCnt(id)-1);

    Vector2 textureDimn = {.x = ad->adImage.texture[ad->adImage.active].width,
                           .y = ad->adImage.texture[ad->adImage.active].height};

    if (textureDimn.x > adArea.width || textureDimn.y > adArea.height)
    {
        free(ad);
        return NULL;
    }

    ad->obj.pos.x = (float)GetRandomValue(adArea.x, adArea.x + adArea.width - textureDimn.x);
    ad->obj.pos.y = (float)GetRandomValue(adArea.y, adArea.y + adArea.height - textureDimn.y);
    
    return ad;
}

void FreeAdverts(Advert* ads[], int adCnt)
{
    for (int i = 0; i < adCnt; i++)
    {
        free(ads[i]);
    }
}