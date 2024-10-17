using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;
using System.Threading.Tasks;

namespace AcSmSheetSetMgr
{
    class AcSmSheet : AcSmClassWithCustomPropertyBag
    {

        protected void SetClass()
        {
            this.ClassName = "AcSmSheet";
            this.clsGuid = Guid.Parse("g16A07941-BC15-4D48-A880-9D5A211D5065");
            this.fID = Guid.NewGuid();
            //this.propname = "Sheet";
            //this.vt = 13;
        }

        public AcSmSheet()
        {
            this.SetClass();
            this.Child.Add(new AcSmProp("Title", 8, "New1"));
        }

        public AcSmSheet(string nName)
        {
            this.SetClass();
            this.Child.Add(new AcSmProp("Title", 8, nName));
        }

        public AcSmSheet(XmlElement wEl) : base(wEl)
        {
        }

        public void SetName(string nName)
        {
            AcSmProp wP = (AcSmProp)this.FindChild("AcSmProp", "Title");
            wP.SetValue(nName);
        }

        public string GetName()
        {
            AcSmProp wP = (AcSmProp)this.FindChild("AcSmProp", "Title");
            return wP.value;
        }

    }
}
