using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;
using System.Threading.Tasks;

namespace AcSmSheetSetMgr
{
    public class AcSmAcDbLayoutReference : AcSmClass
    {
                
        public AcSmAcDbLayoutReference(XmlElement wEl)
            : base(wEl)
        {
        }

        public AcSmAcDbLayoutReference()
        {
            this.ClassName = "AcSmAcDbLayoutReference";
            this.clsGuid = Guid.Parse("94910E94-4FCA-427C-B6ED-2EC9E1C900C7");
            this.fID = Guid.NewGuid();
            this.propname = "DefDwtLayout";
            this.vt = 13;            
        }

    }
}
