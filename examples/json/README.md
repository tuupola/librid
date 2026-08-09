# JSON Example

Demonstrates the `*_to_json()` functions which output message contents as JSON.

```
$ make run
```

## Output

```
{"protocol_version": 2, "message_type": 15, "message_count": 4, "messages": [...]}
```

Output can be prettified with jq.

```
$ make run | jq .
```

```json
{
  "protocol_version": 2,
  "message_type": 15,
  "message_count": 4,
  "messages": [
    {
      "protocol_version": 2,
      "message_type": 0,
      "id_type": 1,
      "ua_type": 2,
      "uas_id": "1ABCD2345EF678XYZ"
    },
    {
      "protocol_version": 2,
      "message_type": 1,
      "latitude": 60.1698570,
      "longitude": 24.9383790,
      "geodetic_altitude": 25.50,
      "pressure_altitude": null,
      "height": 15.00,
      "height_type": 1,
      "speed": 5.25,
      "vertical_speed": null,
      "track_direction": null,
      "operational_status": 2,
      "horizontal_accuracy": 0,
      "vertical_accuracy": 0,
      "speed_accuracy": 0,
      "baro_altitude_accuracy": 0,
      "timestamp": null,
      "timestamp_accuracy": 0
    },
    {
      "protocol_version": 2,
      "message_type": 3,
      "description_type": 0,
      "description": "Survey drone"
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
