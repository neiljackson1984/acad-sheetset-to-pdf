using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;
using System.Threading.Tasks;

namespace AcSmSheetSetMgr
{
    public class AcSmFileReference : AcSmClass
    {

        public AcSmFileReference(XmlElement wEl)
            : base(wEl)
        {
        }

        public AcSmFileReference()
        {
            this.ClassName = "AcSmFileReference";
            this.clsGuid = Guid.Parse("6BF87AE7-1BEC-4BDB-98BB-5B91F7772793");
            this.fID = Guid.NewGuid();
            this.propname = "NewSheetLocation";
            this.vt = 13;
            //
            //this.Child.Add(new AcSmProp("Relative_FileName", 8, ".\\Лист"));
        }

    }
}
