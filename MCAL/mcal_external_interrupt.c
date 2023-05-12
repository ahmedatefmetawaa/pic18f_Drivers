/* 
 * File:   Mcal_external_interrupt.c
 * Author: Ahmed Atef
 *
 * Created on January 1, 2023, 3:26 PM
 */
#include"mcal_external_ interrupt.h"

void (*INT0_INTERRUPT_HANDLER)(void) = NULL;
void (*INT1_INTERRUPT_HANDLER)(void) = NULL;
void (*INT2_INTERRUPT_HANDLER)(void) = NULL;

void (*RB4_INTERRUPT_HANDLER)(void) = NULL;
void (*RB5_INTERRUPT_HANDLER)(void) = NULL;
void (*RB6_INTERRUPT_HANDLER)(void) = NULL;
void (*RB7_INTERRUPT_HANDLER)(void) = NULL;

static Std_ReturnType Interrupt_INTX_Enable (const interrupt_INTX_t *int_obj );
static Std_ReturnType Interrupt_INTX_Disable (const interrupt_INTX_t *int_obj);
static Std_ReturnType Interrupt_INTX_Priority_init (const interrupt_INTX_t *int_obj);
static Std_ReturnType Interrupt_INTX_Edge (const interrupt_INTX_t *int_obj);
static Std_ReturnType Interrupt_INTX_Pin_Init (const interrupt_INTX_t *int_obj);
static Std_ReturnType Interrupt_INTX_Clear_Flag (const interrupt_INTX_t *int_obj);

static Std_ReturnType INT0_SET_INTERRUPT_HANDLER (void (*INTERRUPT_HANDLER)(void));
static Std_ReturnType INT1_SET_INTERRUPT_HANDLER (void (*INTERRUPT_HANDLER)(void));
static Std_ReturnType INT2_SET_INTERRUPT_HANDLER (void (*INTERRUPT_HANDLER)(void)); 
static Std_ReturnType INTERRUPT_INTX_SET_INTERRUPT_HANDLER(const interrupt_INTX_t *int_obj );

static Std_ReturnType Interrupt_RBX_Enable (const interrupt_RBX_t *int_obj );
static Std_ReturnType Interrupt_RBX_Disable (const interrupt_RBX_t *int_obj);
static Std_ReturnType Interrupt_RBX_Priority_init (const interrupt_RBX_t *int_obj);
static Std_ReturnType Interrupt_RBX_Pin_Init (const interrupt_RBX_t *int_obj);

Std_ReturnType Interrupt_INTX_Init   (const interrupt_INTX_t *int_obj )
{
     Std_ReturnType ret = E_OK;
    if(NULL == int_obj )
    {
        ret = E_NOT_OK;
    }
    else{
        /*disable the external interrupt*/
        ret = Interrupt_INTX_Disable(int_obj);
        /*clear flag*/
        ret = Interrupt_INTX_Clear_Flag(int_obj);
        /*configure external interrupt edge*/
        ret = Interrupt_INTX_Edge(int_obj);
        #if INTERRUPT_priority_level_enable == INTERRUPT_FEATURE_ENABLE
        /*configure external interrupt priority*/
        ret = Interrupt_INTX_Priority_init(int_obj);
       #endif
        /*configure external interrupt I/O pin*/
        ret = Interrupt_INTX_Pin_Init(int_obj);
        /*configure default interrupt callback*/
        ret = INTERRUPT_INTX_SET_INTERRUPT_HANDLER(int_obj);
        /*enable the external interrupt*/
        ret = Interrupt_INTX_Enable(int_obj);
    }
     return ret;
}
void INT0_ISR (void)
{
    /*the INT0 occured (must flag bit clear)*/
    EXT_INT0_INTERRUPT_FLAG_CLEAR();
    /*code*/
    
    /*callback function gets call every time this function executed */
    if(INT0_INTERRUPT_HANDLER){INT0_INTERRUPT_HANDLER();} // validate doesn't have null
    
}
void INT1_ISR (void)
{
    /*the INT1 occured (must flag bit clear)*/
    EXT_INT1_INTERRUPT_FLAG_CLEAR();
    /*code*/
    
    /*callback function gets call every time this function executed */
    if(INT1_INTERRUPT_HANDLER){INT1_INTERRUPT_HANDLER();}
    
}
void INT2_ISR (void)
{
    /*the INT2 occured (must flag bit clear)*/
    EXT_INT2_INTERRUPT_FLAG_CLEAR();
    /*code*/
    
    /*callback function gets call every time this function executed */
    if(INT2_INTERRUPT_HANDLER){INT2_INTERRUPT_HANDLER();}
    
}
void RB4_ISR  (void)
{
    /*the int0 occured (must flag bit clear)*/
    EXT_RBX_INTERRUPT_FLAG_CLEAR();
    /*code*/
    
    /*callback function gets call every time this function executed */
    if(RB4_INTERRUPT_HANDLER){RB4_INTERRUPT_HANDLER();}
}
Std_ReturnType Interrupt_INTX_Deinit (const interrupt_INTX_t *int_obj )
{
    Std_ReturnType ret = E_OK;
    if(NULL == int_obj )
    {
        ret = E_NOT_OK;
    }
    else{
        ret = Interrupt_INTX_Disable(int_obj);
    }
     return ret;
}


Std_ReturnType Interrupt_RBX_Init    (const interrupt_RBX_t *RB_obj )
{
    Std_ReturnType ret = E_OK;
    if(NULL == RB_obj )
    {
        ret = E_NOT_OK;
    }
    else{
        /*disable the external interrupt*/
        EXT_RBX_INTERRUPT_DISABLE();
        /*clear flag*/
        EXT_RBX_INTERRUPT_FLAG_CLEAR();
        /*configure external interrupt priority*/
#if INTERRUPT_priority_level_enable == INTERRUPT_FEATURE_ENABLE
            INTERRUPT_PRIORITY_ENABLE();
            if(INTERRUPT_LOW_PRIORITY == RB_obj->priority)
            {EXT_RBX_LOW_PRIORITY();
            NTERRUPT_GIlobalInterruptLowEnable();
            }
            else if(INTERRUPT_HIGH_PRIORITY == RB_obj->priority)
            {EXT_RBX_HIGH_PRIORITY();
            INTERRUPT_GlobalInterruptHighEnable();
            }
            else {/*Nothing*/}
#else
            INTERRUPT_GlobalInterruptEnable();
            INTERRUPT_InterruptPeripheralsEnable();
#endif
        /*configure external interrupt I/O pin*/
            ret = gpio_pin_direction_intialize(&(RB_obj->mcu_pin));
        /*configure default interrupt callback*/
        switch(RB_obj->mcu_pin.pin){
            case GPIO_PIN4 :
                RB4_INTERRUPT_HANDLER = RB_obj->EXT_Interrupt_Handler;
                break;
            case GPIO_PIN5 :
                RB5_INTERRUPT_HANDLER = RB_obj->EXT_Interrupt_Handler;
                break;
            case GPIO_PIN6 :
                RB6_INTERRUPT_HANDLER = RB_obj->EXT_Interrupt_Handler;
                break;
            case GPIO_PIN7 :
                RB7_INTERRUPT_HANDLER = RB_obj->EXT_Interrupt_Handler;
                break;
            default : ret = E_NOT_OK;       
        }    
        /*enable the external interrupt*/
        EXT_RBX_INTERRUPT_ENABLE();
    }
     return ret;
}
Std_ReturnType Interrupt_RBX_Deinit  (const interrupt_RBX_t *RB_obj )
{
    Std_ReturnType ret = E_OK;
    if(NULL == RB_obj )
    {
        ret = E_NOT_OK;
    }
    else{
        
    }
     return ret;
}


/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTX_Enable (const interrupt_INTX_t *int_obj )
{
    Std_ReturnType ret = E_OK;
    if(NULL == int_obj )
    {
        ret = E_NOT_OK;
    }
    else{
        
        switch (int_obj->sorce){
            case INTERRUPT_INT0 :
#if INTERRUPT_priority_level_enable == INTERRUPT_FEATURE_ENABLE

#else
            INTERRUPT_GlobalInterruptEnable();
            INTERRUPT_InterruptPeripheralsEnable();
#endif
            EXT_INT0_INTERRUPT_ENABLE();
            ret = E_OK;
            break;
            
            case INTERRUPT_INT1 :
#if INTERRUPT_priority_level_enable == INTERRUPT_FEATURE_ENABLE
            INTERRUPT_PRIORITY_ENABLE();
            if(INTERRUPT_LOW_PRIORITY == int_obj->priority)
            {INTERRUPT_GlobalInterruptLowEnable();}
            else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority)
            {INTERRUPT_GlobalInterruptHighEnable();}
            else {/*Nothing*/}
#else
            INTERRUPT_GlobalInterruptEnable();
            INTERRUPT_InterruptPeripheralsEnable();
#endif
           EXT_INT1_INTERRUPT_ENABLE();
            ret = E_OK;
            break;
            
            case INTERRUPT_INT2 :
#if INTERRUPT_priority_level_enable == INTERRUPT_FEATURE_ENABLE
            INTERRUPT_PRIORITY_ENABLE();
            if(INTERRUPT_LOW_PRIORITY == int_obj->priority)
            {INTERRUPT_GlobalInterruptLowEnable();}
            else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority)
            {INTERRUPT_GlobalInterruptHighEnable();}
            else {/*Nothing*/}
#else
            INTERRUPT_GlobalInterruptEnable();
            INTERRUPT_InterruptPeripheralsEnable();
#endif
            EXT_INT2_INTERRUPT_ENABLE();
            ret = E_OK;
            break;
            
            default : ret = E_NOT_OK;
        }
    }
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTX_Disable (const interrupt_INTX_t *int_obj)
{
       Std_ReturnType ret = E_OK;
    if(NULL == int_obj )
    {
        ret = E_NOT_OK;
    }
    else{
        switch (int_obj->sorce){
            
            case INTERRUPT_INT0 : EXT_INT0_INTERRUPT_DISABLE();
            ret = E_OK;
            break;
            
            case INTERRUPT_INT1 : EXT_INT1_INTERRUPT_DISABLE();
            ret = E_OK;
            break;
            
            case INTERRUPT_INT2 : EXT_INT2_INTERRUPT_DISABLE();
            ret = E_OK;
            break;
            
            default : ret = E_NOT_OK;
        }  
    }
    return ret; 
}

/**
 * 
 * @param int_obj
 * @return 
 */

static Std_ReturnType Interrupt_INTX_Priority_init (const interrupt_INTX_t *int_obj)
{
        Std_ReturnType ret = E_OK;
    if(NULL == int_obj )
    {
        ret = E_NOT_OK;
    }
    else
    {
    #if INTERRUPT_priority_level_enable == INTERRUPT_FEATURE_ENABLE    
        switch (int_obj->sorce){
          
            case INTERRUPT_INT1 : if(INTERRUPT_LOW_PRIORITY == int_obj->priority){EXT_INT1_LOW_PRIORITY_SET();}
            else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){EXT_INT1_HIGH_PRIORITY_SET();}
            else {/*Nothing*/}
            ret = E_OK;
            break;
            
            case INTERRUPT_INT2 :if(INTERRUPT_LOW_PRIORITY == int_obj->priority){EXT_INT2_LOW_PRIORITY_SET();}
            else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){EXT_INT2_HIGH_PRIORITY_SET();}
            else {/*Nothing*/}
            ret = E_OK;
            break;
            
            default : ret = E_NOT_OK;
        }
   #endif 
    }
   
    return ret;
}


/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTX_Edge (const interrupt_INTX_t *int_obj)
{
        Std_ReturnType ret = E_OK;
    if(NULL == int_obj )
    {
        ret = E_NOT_OK;
    }
    else{
        switch (int_obj->sorce){
            
            case INTERRUPT_INT0 : if(FALLING_EDGE == int_obj->edge){EXT_INT0_INTERRUPT_FALLINGEDGE();}
            else if(RISING_EDGE == int_obj->edge){EXT_INT0_INTERRUPT_RISINGEDGE();}
            else {/*Nothing*/}
            ret = E_OK;
            break;
            
            case INTERRUPT_INT1 : if(FALLING_EDGE == int_obj->edge){EXT_INT1_INTERRUPT_FALLINGEDGE();}
            else if(RISING_EDGE == int_obj->edge){EXT_INT1_INTERRUPT_RISINGEDGE();}
            else {/*Nothing*/}
            ret = E_OK;
            break;
            
            case INTERRUPT_INT2 :if(FALLING_EDGE == int_obj->edge){EXT_INT2_INTERRUPT_FALLINGEDGE();}
            else if(RISING_EDGE == int_obj->edge){EXT_INT2_INTERRUPT_RISINGEDGE();}
            else {/*Nothing*/}
            ret = E_OK;
            break;
            
            default : ret = E_NOT_OK;
        }
    }
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTX_Pin_Init (const interrupt_INTX_t *int_obj)
{
        Std_ReturnType ret = E_OK;
    if(NULL == int_obj )
    {
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_direction_intialize(&(int_obj->mcu_pin));
    }
    return ret;
}
/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTX_Clear_Flag (const interrupt_INTX_t *int_obj)
{
        Std_ReturnType ret = E_OK;
    if(NULL == int_obj )
    {
        ret = E_NOT_OK;
    }
    else{
        
        switch (int_obj->sorce){
            case INTERRUPT_INT0 : EXT_INT0_INTERRUPT_FLAG_CLEAR();
            ret = E_OK;
            break;
            
            case INTERRUPT_INT1 : EXT_INT1_INTERRUPT_FLAG_CLEAR();
            ret = E_OK;
            break;
            
            case INTERRUPT_INT2 : EXT_INT2_INTERRUPT_FLAG_CLEAR();
            ret = E_OK;
            break;
            
            default : ret = E_NOT_OK;
        }
    }
    return ret;
}



static Std_ReturnType INT0_SET_INTERRUPT_HANDLER (void (*INTERRUPT_HANDLER)(void))
{
    Std_ReturnType ret = E_OK;
    if(NULL == INTERRUPT_HANDLER )
    {
        ret = E_NOT_OK;
    }
    else{
        INT0_INTERRUPT_HANDLER = INTERRUPT_HANDLER;
    } 
    return ret;
}

static Std_ReturnType INT1_SET_INTERRUPT_HANDLER (void (*INTERRUPT_HANDLER)(void))
{
    Std_ReturnType ret = E_OK;
    if(NULL == INTERRUPT_HANDLER )
    {
        ret = E_NOT_OK;
    }
    else{
        INT1_INTERRUPT_HANDLER = INTERRUPT_HANDLER;
    } 
    return ret;
}

static Std_ReturnType INT2_SET_INTERRUPT_HANDLER (void (*INTERRUPT_HANDLER)(void))
{
    Std_ReturnType ret = E_OK;
    if(NULL == INTERRUPT_HANDLER )
    {
        ret = E_NOT_OK;
    }
    else{
        INT2_INTERRUPT_HANDLER = INTERRUPT_HANDLER;
    } 
    return ret;
}

static Std_ReturnType INTERRUPT_INTX_SET_INTERRUPT_HANDLER(const interrupt_INTX_t *int_obj )
{
    Std_ReturnType ret = E_OK;
    if(NULL == int_obj )
    {
        ret = E_NOT_OK;
    }
    else{
        
        switch (int_obj->sorce){
            case INTERRUPT_INT0 : ret = INT0_SET_INTERRUPT_HANDLER(int_obj->EXT_Interrupt_Handler);
            break;
            
           case INTERRUPT_INT1  : ret = INT1_SET_INTERRUPT_HANDLER(int_obj->EXT_Interrupt_Handler);
            break;
            
            case INTERRUPT_INT2 : ret = INT2_SET_INTERRUPT_HANDLER(int_obj->EXT_Interrupt_Handler);
            break;
            
            default : ret = E_NOT_OK;
        }
    }
    return ret;
}
/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_RBX_Enable (const interrupt_RBX_t *int_obj )
{
    
}
/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_RBX_Disable (const interrupt_RBX_t *int_obj)
{
    
}
/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_RBX_Priority_init (const interrupt_RBX_t *int_obj)
{
    
}
/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_RBX_Pin_Init (const interrupt_RBX_t *int_obj)
{
    
}