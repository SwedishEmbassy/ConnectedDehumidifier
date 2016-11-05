# Connected Dehumidifier
We bought a dehumidifier for our living space. But it's not connected to anything. Let's give it internet.

## Current functionality
Listen on serial (9600) for events. Currently there are two events implemented, and one command.

### Commands
#### Turn on or off
Write `toggle_power` to serial to toggle the power state. You'll receive a on/off state changed event describing the new state.

### JSON Events
#### On/Off state changed
When someone turns the dehumidifier on or off via its button, or via the `toggle_power` command, a JSON event is printed to serial:
```json
ON:
{"event": "on_state_changed", "new_value": 1}

OFF:
{"event": "on_state_changed", "new_value": 0}

```

#### Water tank state changed
The Dehumidifer we use has a water tank built in. When this one becomes full (or someone empties it), a JSON event is printed to serial:
```json
TANK FULL:
{"event": "full_state_changed", "new_value": 1}

TANK NOT FULL:
{"event": "full_state_changed", "new_value": 0}

```

## Photos
Photos taken during hackathon when this was implemented:

![](http://i.imgur.com/oHc91VB.jpg)
![](http://i.imgur.com/rNNoyPi.jpg)
![](http://i.imgur.com/pcVaDGY.jpg)
