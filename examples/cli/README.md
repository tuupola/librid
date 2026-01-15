# CLI Example

Decode hex-encoded Remote ID messages to JSON.

```
$ make
$ ./rid <hex_string>
$ ./rid < file.hex
```

## Supported Formats

- **25 bytes**: Remote ID message
- **27 bytes**: Application Code + Counter + Remote ID message

## Example

```
$ ./rid 12202d3e0420bd5c25401c190d0000c10834084a0339300100 | jq
$ echo "12202d3e0420bd5c25401c190d0000c10834084a0339300100" | ./rid | jq
```

```json
{
  "protocol_version": 2,
  "message_type": 1,
  "latitude": 62.683472,
  "longitude": 21.974944,
  "geodetic_altitude": 120.500000,
  "pressure_altitude": -1000.000000,
  "height": 50.000000,
  "height_type": 0,
  "speed": 15.500000,
  "vertical_speed": 2.000000,
  "track_direction": 45,
  "operational_status": 2,
  "horizontal_accuracy": 10,
  "vertical_accuracy": 4,
  "speed_accuracy": 3,
  "baro_altitude_accuracy": 0,
  "timestamp": 12345,
  "timestamp_accuracy": 1
}
```

## Remote ID Scanner

You can create a poor man's Remote ID scanner if your computer supports bluetooth.
First start scanning with `bluetoothctl`.

```
$ bluetoothctl
[bluetoothctl]> scan le
```

Keep `bluetoothctl` running and on another terminal capture messages with `btmon`
and feed them to this example CLI.

```
$ sudo btmon | grep -i -A 1 "0xfffa" | grep -oP 'Data\[\d+\]: \K[0-9a-f]+' | ./rid
```

