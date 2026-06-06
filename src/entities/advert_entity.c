#include "advert_entity.h"

#include "entity_manager.h"

void InitAdverts(Advert* ads[], int adCnt)
{
    for (int i = 0; i < adCnt; i++)
        ads[i] = NULL;
}

void SpawnAdvert(Advert* ads[], int adCnt, Rectangle playArea)
{        
    static int horBannerCnt = 0;
    static int vertBannerCnt = 0;
    static int smallRectCnt = 0;
    static int bigRectCnt = 0;

    int seed = GetRandomValue(0, AD_RANGE_MAX);
    if (seed > AD_HOR_BANNER_RATE && horBannerCnt <= AD_RANGE_MAX - AD_HOR_BANNER_RATE)
    {

    } 
    else if (seed > AD_VERT_BANNER_RATE && vertBannerCnt <= MAX_VERT_BANNER_CNT)
    {
        
    }
    else if (seed > AD_SMALL_RECT_RATE && smallRectCnt <= MAX_SMALL_RECT_CNT)
    {

    }
    else if ()
    {

    }
}

Advert* CreateAdvert(Rectangle adArea)
{
    Advert* ad = (Advert*)malloc(1 * sizeof(Advert));
    ad->obj.id = ENTITY_AD;
    ad->adImage.active = //get random int for active
    ad->adImage.texture = //set the random active one

    switch (adSize)
    {
    case AD_HOR_BANNER:
        ad->obj.pos.x = playArea.width / 2;
        ad->obj.pos.y = (playArea.height + playArea.y);
        break;
    case AD_VERT_BANNER:
        
        break;
    case AD_SMALL_RECT:
        
        break;
    case AD_BIG_RECT:
        
        break;
    
    default:
        fprintf(stderr, "[ERROR]: Unknown ad size!\n");
        free(ad);
        return NULL;
    }

    return ad;
}