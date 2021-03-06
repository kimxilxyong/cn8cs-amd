/* XMRig
 * Copyright 2010      Jeff Garzik <jgarzik@pobox.com>
 * Copyright 2012-2014 pooler      <pooler@litecoinpool.org>
 * Copyright 2014      Lucas Jones <https://github.com/lucasjones>
 * Copyright 2014-2016 Wolf9466    <https://github.com/OhGodAPet>
 * Copyright 2016      Jay D Dee   <jayddee246@gmail.com>
 * Copyright 2017-2018 XMR-Stak    <https://github.com/fireice-uk>, <https://github.com/psychocrypt>
 * Copyright 2018-2019 SChernykh   <https://github.com/SChernykh>
 * Copyright 2016-2019 XMRig       <https://github.com/xmrig>, <support@xmrig.com>
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef XMRIG_OCLTHREAD_H
#define XMRIG_OCLTHREAD_H


#include "common/xmrig.h"
#include "interfaces/IThread.h"
#include "amd/CoolingContext.h"
//#include "amd/AdlUtils.h"


struct GpuContext;


namespace xmrig {


class OclThread : public xmrig::IThread
{
public:
    OclThread();
    OclThread(const rapidjson::Value &object);
    OclThread(size_t index, size_t intensity, size_t worksize, int64_t affinity = -1);

    //~OclThread();
    ~OclThread() override;

    inline GpuContext *ctx() const  { return m_ctx; }
    inline void setAffinity(int64_t affinity) { m_affinity = affinity; }

    inline void setCardId(int cardid) { m_cardId = cardid; }
    inline void setThreadId(int threadid) { m_threadId = threadid; }
    inline int cardId() const { return m_cardId; }
    inline int threadId() const { return m_threadId; }

    inline void setPciBusID(uint32_t pciBusID) { m_pciBusID = pciBusID; }
    inline void setPciDeviceID(uint32_t pciDeviceID) { m_pciDeviceID = pciDeviceID; }
    inline void setPciDomainID(uint32_t pciDomainID) { m_pciDomainID = pciDomainID; }
    inline uint32_t pciBusID() const { return m_pciBusID; }
    inline uint32_t pciDeviceID() const { return m_pciDeviceID; }
    inline uint32_t pciDomainID() const { return m_pciDomainID; }

    //inline xmrig::Algo algorithm() const override { return m_algorithm; }
    inline Algo algorithm() const override        { return m_algorithm; }
    inline int priority() const override          { return -1; }
    inline int64_t affinity() const override      { return m_affinity; }
    inline Multiway multiway() const override     { return SingleWay; }
    inline Type type() const override             { return OpenCL; }
    inline bool isValid() const override          { return intensity() > 0 && worksize() > 0; }

    size_t index() const override;

    bool isCompMode() const;
    int memChunk() const;
    int stridedIndex() const;
    int unrollFactor() const;
    size_t intensity() const;
    size_t worksize() const;
    void setCompMode(bool enable);
    void setIndex(size_t index);
    void setIntensity(size_t intensity);
    void setMemChunk(int memChunk);
    void setStridedIndex(int stridedIndex);
    void setThreadsCountByGPU(size_t threads);
    void setUnrollFactor(int unrollFactor);
    void setWorksize(size_t worksize);

    inline CoolingContext* cool() const { return m_cool; }
    inline void setCoolingContext(CoolingContext *cool) {m_cool = cool; }

protected:
#   ifdef APP_DEBUG
    void print() const override;
#   endif

#   ifndef XMRIG_NO_API
    rapidjson::Value toAPI(rapidjson::Document &doc) const override;
#   endif

    rapidjson::Value toConfig(rapidjson::Document &doc) const override;

private:
    GpuContext *m_ctx;
    int64_t m_affinity;
    xmrig::Algo m_algorithm;

    int m_cardId;
    int m_threadId;

    uint32_t m_pciBusID;
    uint32_t m_pciDeviceID;
    uint32_t m_pciDomainID;

    CoolingContext *m_cool;
};


} /* namespace xmrig */


#endif /* XMRIG_OCLTHREAD_H */
