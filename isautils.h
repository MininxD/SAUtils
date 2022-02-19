#include <stdint.h>

typedef void        (*OnSettingChangedFn)(int nOldValue, int nNewValue);
typedef const char* (*OnSettingDrawedFn) (int nNewValue);
typedef void        (*OnButtonPressedFn) (uintptr_t screen); // Screen is just a pointer of SelectScreen if you need it...

enum eTypeOfSettings : unsigned char
{
    Controller = 0,
    Game = 1,
    Display = 2,
    Audio = 3,
    Language = 4,
    Mods = 5,

    SETTINGS_COUNT,
};

enum eTypeOfItem : unsigned char
{
    WithItems = 0,
    Slider = 1,
    Button = 2,

    ITEMTYPES_COUNT,
};

class ISAUtils
{
public:
/* Functions below added in 1.0.0.0 */

    /** Get an address of Fastman Limit Adjuster if included
     *
     *  \return Address of a FLA library
     */
    virtual uintptr_t IsFLALoaded() = 0;
    
    // switchesArray is an array of items of clickable item (byteItemType = WithItems)
    #if __cplusplus >= 201300 // Do not create errors on C++11 and lower :P
      [[deprecated("Use AddClickableItem or AddSliderItem")]]
    #endif
    virtual int AddSettingsItem(eTypeOfSettings typeOf, const char* name, int initVal = 0, int minVal = 0, int maxVal = 0, OnSettingChangedFn fnOnValueChange = NULL, bool isSlider = false, void* switchesArray = NULL) = 0;

    /** Get a value of setting (returned by AddClickableItem or AddSliderItem)
     *
     *  \param settingId Numeric ID of setting (0-200 for example)
     *  \return Value of that setting
     */
    virtual int ValueOfSettingsItem(int settingId) = 0;

/* Functions below added in 1.1.0.0 */

    /** Adds clickable text button in menu settings
     *
     *  \param typeOf In which setting option that item should be added
     *  \param name Obviously a displayed name
     *  \param initVal Initial value (def: 0)
     *  \param minVal Minimum value (def: 0)
     *  \param maxVal Maximum value (def: 0)
     *  \param switchesArray An array that includes names of options
     *  \param fnOnValueChange A function that will be called on value being saved (def: null)
     *  \return Setting ID
     */
    virtual int AddClickableItem(eTypeOfSettings typeOf, const char* name, int initVal = 0, int minVal = 0, int maxVal = 0, const char** switchesArray = NULL, OnSettingChangedFn fnOnValueChange = NULL) = 0;

    /** Adds a slider in menu settings
     *
     *  \param typeOf In which setting option that item should be added
     *  \param name Obviously a displayed name
     *  \param initVal Initial value (def: 0)
     *  \param minVal Minimum value (def: 0)
     *  \param maxVal Maximum value (def: 0)
     *  \param fnOnValueChange A function that will be called on value being saved (def: null)
     *  \param fnOnValueDraw A function that will control a text of a slider (def: null)
     *  \return Setting ID
     */
    virtual int AddSliderItem(eTypeOfSettings typeOf, const char* name, int initVal = 0, int minVal = 0, int maxVal = 0, OnSettingChangedFn fnOnValueChange = NULL, OnSettingDrawedFn fnOnValueDraw = NULL) = 0;

    /** Adds a clickable button in menu settings
     *
     *  \param typeOf In which setting option that item should be added
     *  \param name Obviously a displayed name
     *  \param fnOnButtonPressed A function that will be called on button press (def: null)
     */
    virtual void AddButton(eTypeOfSettings typeOf, const char* name, OnButtonPressedFn fnOnButtonPressed = NULL) = 0;
};