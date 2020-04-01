#ifndef EFFECT_DESIGN_EFFECT_DESIGNER_H
#define EFFECT_DESIGN_EFFECT_DESIGNER_H

#include <stdint.h>

class EffectDesigner
{
    float m_samplingFrequency;

    uint8_t m_effectCode;
    uint8_t m_dataSize;
    const uint8_t* m_data;

    bool m_isDirty;

public:
    EffectDesigner(float samplingFrequency, uint8_t effectCode, uint8_t dataSize, const uint8_t* data);
    virtual ~EffectDesigner();

    float samplingFrequency() const;

    uint8_t effectCode() const;
    uint8_t dataSize() const;
    const uint8_t* data() const;

    bool isDirty() const;
    void setIsDirty(bool isDirty);
};

inline float EffectDesigner::samplingFrequency() const
{
    return m_samplingFrequency;
}

inline uint8_t EffectDesigner::effectCode() const
{
    return m_effectCode;
}

inline uint8_t EffectDesigner::dataSize() const
{
    return m_dataSize;
}

inline const uint8_t* EffectDesigner::data() const
{
    return m_data;
}

inline bool EffectDesigner::isDirty() const
{
    return m_isDirty;
}

inline void EffectDesigner::setIsDirty(bool isDirty)
{
    m_isDirty = isDirty;
}

#endif
