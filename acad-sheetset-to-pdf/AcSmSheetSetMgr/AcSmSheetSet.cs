using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;
using System.Threading.Tasks;

namespace AcSmSheetSetMgr
{
    public class AcSmSheetSet : AcSmClassWithCustomPropertyBag
    {

        protected void SetClass()
        {
            this.ClassName = "AcSmSheetSet";
            this.clsGuid = Guid.Parse("B20534F2-0978-418C-8D14-2E6928A077ED");
            this.fID = Guid.NewGuid();
            this.propname = "SheetSet";
            this.vt = 13;
        }

        public AcSmSheetSet()
        {
            this.SetClass();
            this.Child.Add(new AcSmProp("Name", 8, "New1"));
        }

        public AcSmSheetSet(string nName)
        {
            this.SetClass();
            this.Child.Add(new AcSmProp("Name", 8, nName));
        }

        public AcSmSheetSet(XmlElement wEl) : base(wEl)
        {
        }

        public void SetName(string nName)
        {
            AcSmProp wP = (AcSmProp)this.FindChild("AcSmProp", "Name");
            wP.SetValue(nName);
        }

        public AcSmSubset GetSubset(string nName)
        {
            List<AcSmClass> wList = this.FindAllChild("AcSmSubset");
            //
            if (wList != null)
            {
                if (wList.Exists(x => ((AcSmSubset)x).GetNameProp().value == nName))
                {
                    return (AcSmSubset)wList.Find(x => ((AcSmSubset)x).GetNameProp().value == nName);
                }
            }

            return null; 
        }

        public AcSmSubset AddSubset(string nName)
        {
            AcSmSubset nSS = this.GetSubset(nName);
            if (nSS == null)
            {
                nSS = new AcSmSubset(nName);
                this.Child.Add(nSS);
            }
            return nSS;
        }

    }
}
