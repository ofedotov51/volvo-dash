#ifndef SENSOR_MAP_H
#define SENSOR_MAP_H

#include <sensor.h>
#include <sensor_source_adc.h>
#include <map_sensor.h>

class Map_Sensor : public Sensor {
public:
    Map_Sensor(QObject * parent, Config * config,
               AdcSource * source, int channel) :
    Sensor(parent, config, source, channel) {
        // setup map sensor
        mMapSensor = new MapSensor(
                    mConfig->getMapSensorConfig().p0V,
                    mConfig->getMapSensorConfig().p5V,
                    mConfig->getMapSensorConfig().units
                    );
    }



public slots:
    void transform(QVariant data, int channel) override {
        if (channel == getChannel()) {
            qreal volts = data.toReal();
            qreal pressure = mMapSensor->getAbsolutePressure(volts, Config::PressureUnits::PSI) - 14.5038;
            emit sensorDataReady(pressure);
        }
    }

private:
    MapSensor * mMapSensor;
};

#endif // SENSOR_MAP_H
