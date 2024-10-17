using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;
using System.Threading.Tasks;

namespace AcSmSheetSetMgr
{
    public class AcSmProp : AcSmClass
    {

        public AcSmProp(XmlElement wEl)
            : base(wEl)
        {
        }

        public AcSmProp(string nPropname, int nvt, string nValue)
        {
            this.ClassName = "AcSmProp";
            this.propname = nPropname;
            this.vt = nvt;
            this.value = nValue;
        }

        public string Name
        {
            get { return this.propname; }
        }

        public void SetValue(string nValue)
        {
            this.value = nValue;
        }
    }
}
