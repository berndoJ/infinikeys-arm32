# Table of Contents

- [Module Descriptions](#module-descriptions)
  * [infinikeys_acq.h](#infinikeys-acqh)
    + [_IK_ACQ_Config](#-ik-acq-config)



# Module Descriptions

## infinikeys_acq.h

### _IK_ACQ_Config

```c
void _IK_ACQ_Config(uint8_t* p_pressedkeys_table, uint16_t pressedkeys_table_size, void (*poll_callback_func)(void));
```

**Description**

Configures the InfiniKeys key state acquisition module.

**Parameters**

- `uint8_t* p_pressedkeys_table`: Pointer to the pressed keys table the acquisition module should use.
- `uint16_t pressedkeys_table_size`: Size of the pressed keys table.
- `void (*poll_callback_func)(void)`: Poll finished callback function pointer.

### _IK_ACQ_Poll

```c
void _IK_ACQ_Poll(void);
```

**Description**

Initiates a new keyboard matrix state poll.