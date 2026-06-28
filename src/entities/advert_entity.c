#include "advert_entity.h"

static int adTypeCnt[AD_TYPE_CNT];

void InitAdverts(AdvertArray* adArr, int maxCnt, double cooldownTime)
{
    adArr->maxAdCnt = maxCnt;
    adArr->ads = malloc(sizeof(Advert*) * (size_t)maxCnt);
    adArr->adCnt = 0;
    adArr->spawnTimeCooldown = cooldownTime;

    for (int i = 0; i < AD_TYPE_CNT; i++)
        adTypeCnt[i] = 0;
}

void ResetAdverts(AdvertArray* adArr, double curTime)
{
    adArr->spawnTimer = curTime;
    for (int i = 0; i < adArr->adCnt; i++)
    {
        free(adArr->ads[i]);
        adArr->ads[i] = NULL;
    }
    adArr->adCnt = 0;
 
    for (int i = 0; i < AD_TYPE_CNT; i++)
        adTypeCnt[i] = 0;
}

bool SpawnAdvert(AdvertArray* adArr, Rectangle playArea)
{   
    if (adArr->adCnt >= adArr->maxAdCnt) return false;

    int seed = GetRandomValue(0, AD_TYPE_CNT-1);
    
    while (true)
    {
        if (seed == AD_HOR && adTypeCnt[AD_HOR] < AD_HOR_BANNER_CNT)
        {
            adArr->ads[adArr->adCnt] = CreateAdvert(AD_HOR, 
                    AD_HOR_BANNER_AREA(playArea.x, playArea.y, playArea.width, playArea.height));
            break;
        }

        else if (seed == AD_VERT_LEFT && adTypeCnt[AD_VERT_LEFT] < AD_VERT_LEFT_BANNER_CNT)
        {
            adArr->ads[adArr->adCnt] = CreateAdvert(AD_VERT_LEFT, 
                AD_VERT_LEFT_BANNER_AREA(playArea.x, playArea.y, playArea.width, playArea.height));
            break;
        }

        else if (seed == AD_VERT_RIGHT && adTypeCnt[AD_VERT_RIGHT] < AD_VERT_RIGHT_BANNER_CNT)
        {
            adArr->ads[adArr->adCnt] = CreateAdvert(AD_VERT_RIGHT, 
                AD_VERT_RIGHT_BANNER_AREA(playArea.x, playArea.y, playArea.width, playArea.height));
            break;
        }

        else if (seed == AD_RECT && adTypeCnt[AD_RECT] < AD_RECT_CNT)
        {
            adArr->ads[adArr->adCnt] = CreateAdvert(AD_RECT, 
                AD_RECT_AREA(playArea.x, playArea.y, playArea.width, playArea.height));
            break;
        }

        seed = (seed+1)%AD_TYPE_CNT;
    }

    if (adArr->ads[adArr->adCnt] == NULL) return false;

    adTypeCnt[seed]++;
    adArr->adCnt++;
    return true;
}

Advert* CreateAdvert(enum AdTypes adId, Rectangle adArea)
{
    Advert* ad = malloc(1 * sizeof(Advert));
    if (ad == NULL)
    {
        fprintf(stderr, "[ERROR]: Failed to allocate memory for ad!\n");
        return NULL;
    }
    
    ad->adType = adId;
    ad->obj.id = ENTITY_AD;
    ad->selected = false;
    ad->adImage.textures = *GetAdvertTexture(adId);
    ad->adImage.active = GetRandomValue(0, ad->adImage.textures.cnt -1);

    Vector2 textureDimn = {.x = (float)ad->adImage.textures.textures[ad->adImage.active].width,
                           .y = (float)ad->adImage.textures.textures[ad->adImage.active].height};
        
    if (textureDimn.x > adArea.width || textureDimn.y > adArea.height)
    {
        free(ad);
        return NULL;
    }

    ad->obj.pos.x = (float)GetRandomValue((int)adArea.x, (int)(adArea.x + adArea.width - textureDimn.x));
    ad->obj.pos.y = (float)GetRandomValue((int)adArea.y, (int)(adArea.y + adArea.height - textureDimn.y));

    ad->closeBox.active = 0;
    ad->closeBox.textures.textures = GetCloseButtonTexture();

    return ad;
}

void ClearAdvertSelection(AdvertArray* adArr)
{
    for (int i = 0; i < adArr->adCnt; i++)
    {
        adArr->ads[i]->selected = false;
        adArr->ads[i]->closeBox.active = AD_HOVER_OVER_HITBOX_FALSE;
    }
}

void AdvertPlayerCollision(AdvertArray* adArr, Rectangle pHitbox, bool isHit)
{
    int removed = 0;

    for (int i = 0; i < adArr->adCnt; i++)
    {
        Advert* curAd = adArr->ads[i];
        Rectangle adHitbox = {(float)curAd->adImage.textures.textures[curAd->closeBox.active].width + curAd->obj.pos.x - AD_CLOSE_HITBOX.x, 
                              curAd->obj.pos.y, AD_CLOSE_HITBOX.x, AD_CLOSE_HITBOX.y}; 
        if (CheckCollisionRecs(pHitbox, adHitbox)) 
        {
            curAd->selected = true;
            curAd->closeBox.active = AD_HOVER_OVER_HITBOX_TRUE;

            if (isHit)
            {
                AssetsPlaySound(SFX_CLOSE_AD);
                adTypeCnt[curAd->adType]--;

                free(adArr->ads[i]);
                adArr->ads[i] = NULL;
                removed++;
            }
        }
    }

    ReorderAdArray(adArr);
    adArr->adCnt -= removed;
}

void ReorderAdArray(AdvertArray* adArr)
{
    for (int i = 0; i < adArr->adCnt; i++)
    {
        if (adArr->ads[i] != NULL) continue;
        for (int j = i+1; j < adArr->adCnt; j++)
        {
            if (adArr->ads[j] == NULL) continue;

            adArr->ads[i] = adArr->ads[j];
            adArr->ads[j] = NULL;
            break;
        }
    }
}

void FreeAdverts(AdvertArray* adArr)
{
    for (int i = 0; i < adArr->adCnt; i++)
        free(adArr->ads[i]);
    free(adArr->ads);
}