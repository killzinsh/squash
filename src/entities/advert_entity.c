#include "advert_entity.h"

void InitAdverts(AdvertArray* adArr, int maxCnt, double cooldownTime)
{
    adArr->maxAdCnt = maxCnt;
    adArr->ads = malloc(sizeof(Advert*) * (size_t)maxCnt);
    adArr->adCnt = 0;
    adArr->spawnTimeCooldown = cooldownTime;    
}

void ResetAdverts(AdvertArray* adArr, double curTime)
{
    adArr->spawnTimer = curTime;
    for (int i = 0; i < adArr->adCnt; i++)
        free(adArr->ads[i]);
}

bool SpawnAdvert(AdvertArray* adArr, Rectangle playArea)
{   
    if (adArr->adCnt+1 >= adArr->maxAdCnt) return false;

    static int horBannerCnt = 0;
    static int vertBannerCnt = 0;
    static int rectCnt = 0;

    int seed = GetRandomValue(0, AD_RANGE_MAX);
    if (seed <= AD_HOR_BANNER_RATE && horBannerCnt <= MAX_HOR_BANNER_CNT)
    {
        adArr->ads[adArr->adCnt] = CreateAdvert(ENTITY_AD_HOR_BANNER, 
            AD_HOR_BANNER_AREA(playArea.x, playArea.y, playArea.width, playArea.height));
        horBannerCnt++;
    } 
    
    else if (seed <= AD_VERT_LEFT_BANNER_RATE && vertBannerCnt <= MAX_VERT_BANNER_CNT)
    {
        adArr->ads[adArr->adCnt] = CreateAdvert(ENTITY_AD_VERT_BANNER, 
            AD_VERT_LEFT_BANNER_AREA(playArea.x, playArea.y, playArea.width, playArea.height));
        vertBannerCnt++;        
    }

    else if (seed <= AD_VERT_RIGHT_BANNER_RATE && vertBannerCnt <= MAX_VERT_BANNER_CNT)
    {
        adArr->ads[adArr->adCnt] = CreateAdvert(ENTITY_AD_VERT_BANNER, 
            AD_VERT_RIGHT_BANNER_AREA(playArea.x, playArea.y, playArea.width, playArea.height));
        vertBannerCnt++;
    }

    else if (seed <= AD_RECT_RATE && rectCnt <= MAX_SMALL_RECT_CNT)
    {
        adArr->ads[adArr->adCnt] = CreateAdvert(ENTITY_AD_RECT, 
            AD_RECT_AREA(playArea.x, playArea.y, playArea.width, playArea.height));
        rectCnt++;
    }

    if (adArr->ads[adArr->adCnt] == NULL) return false;

    adArr->adCnt++;
    return true;
}

Advert* CreateAdvert(enum EntityId id, Rectangle adArea)
{
    Advert* ad = malloc(1 * sizeof(Advert));
    if (ad == NULL)
    {
        fprintf(stderr, "[ERROR]: Failed to allocate memory for ad!\n");
        return NULL;
    }
    
    ad->obj.id = id;
    ad->selected = false;
    ad->adImage.texture = GetEntityTextures(id);
    ad->adImage.active = GetRandomValue(0, GetEntityTextureCnt(id)-1);

    Vector2 textureDimn = {.x = (float)ad->adImage.texture[ad->adImage.active].width,
                           .y = (float)ad->adImage.texture[ad->adImage.active].height};
        
    if (textureDimn.x > adArea.width || textureDimn.y > adArea.height)
    {
        free(ad);
        return NULL;
    }

    ad->obj.pos.x = (float)GetRandomValue(adArea.x, adArea.x + adArea.width - textureDimn.x);
    ad->obj.pos.y = (float)GetRandomValue(adArea.y, adArea.y + adArea.height - textureDimn.y);

    ad->closeBox.active = 0;
    ad->closeBox.texture = GetCloseButtonTexture();

    return ad;
}

void AdvertPlayerCollision(AdvertArray* adArr, Rectangle pHitbox, bool isHit)
{
    int removed = 0;

    for (int i = 0, j = 0; i < adArr->adCnt; i++)
    {
        Rectangle adHitbox = {adArr->ads[i]->adImage.texture[adArr->ads[i]->closeBox.active].width + adArr->ads[i]->obj.pos.x - AD_CLOSE_HITBOX.x, 
                              adArr->ads[i]->obj.pos.y, AD_CLOSE_HITBOX.x, AD_CLOSE_HITBOX.y}; 
        if (CheckCollisionRecs(pHitbox, adHitbox)) 
        {
            adArr->ads[i]->selected = true;
            adArr->ads[i]->closeBox.active = AD_HOVER_OVER_HITBOX_TRUE;
        }
        else 
        {
            adArr->ads[i]->selected = false;
            adArr->ads[i]->closeBox.active = AD_HOVER_OVER_HITBOX_FALSE;
        }

        if (adArr->ads[i]->selected && isHit)
        {
            free(adArr->ads[i]);
            removed++;
        }

        else
        {
            adArr->ads[j] = adArr->ads[i];
            j++;
        }
    }

    adArr->adCnt -= removed;
}

void FreeAdverts(AdvertArray* adArr)
{
    for (int i = 0; i < adArr->adCnt; i++)
        free(adArr->ads[i]);
    free(adArr->ads);
}