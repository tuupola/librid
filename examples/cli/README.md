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
  "latitude": 65.634037,
  "longitude": 25.255144,
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
[bluetoothctl]> power on
[bluetoothctl]> scan le
```

Keep `bluetoothctl` running and on another terminal capture messages with `tshark`
and feed them to the example CLI.

```
$ sudo tshark -q -l -i bluetooth0 \
  -Y "btcommon.eir_ad.entry.uuid_16 == 0xfffa" \
  -T fields -e btcommon.eir_ad.entry.service_data | \
  ./rid | jq
```
```json
{
  "counter": 216,
  "protocol_version": 2,
  "message_type": 15,
  "message_count": 4,
  "messages": [
    {
      "protocol_version": 2,
      "message_type": 0,
      "id_type": 1,
      "ua_type": 0,
      "uas_id": "1596A303716531B"
    },
    {
      "protocol_version": 2,
      "message_type": 1,
      "latitude": 65.634037,
      "longitude": 25.255144,
      "geodetic_altitude": 102.500000,
      "pressure_altitude": 104.500000,
      "height": -0.500000,
      "height_type": 0,
      "speed": 0.000000,
      "vertical_speed": 0.000000,
      "track_direction": 74,
      "operational_status": 2,
      "horizontal_accuracy": 10,
      "vertical_accuracy": 5,
      "speed_accuracy": 4,
      "baro_altitude_accuracy": 0,
      "timestamp": 13880,
      "timestamp_accuracy": 0
    },
    {
      "protocol_version": 2,
      "message_type": 4,
      "operator_location_type": 0,
      "classification_type": 1,
      "ua_classification_category": 1,
      "ua_classification_class": 0,
      "operator_latitude": 65.634037,
      "operator_longitude": 25.255144,
      "operator_altitude": 107.500000,
      "area_count": 1,
      "area_radius": 0,
      "area_ceiling": -1000.000000,
      "area_floor": -1000.000000,
      "timestamp": 225282188
    },
    {
      "protocol_version": 2,
      "message_type": 5,
      "id_type": 0,
      "operator_id": "FIN87astrdge12k8"
    }
  ]
}
```

You could also use `btmon` but this is more brittle. Different versions might require different regexp to work.

```
$ sudo btmon | grep -i -A 1 "0xfffa" | grep -oP '^\s+Data: \K[0-9a-f]+' | ./rid | jq
```
